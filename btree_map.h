#ifndef BTREE_MAP_H_
#define BTREE_MAP_H_

#include <stdexcept>
#include <vector>

// A B-tree based ordered map.
//
// A B-tree of order M is an M-ary search tree:
//   - Each internal node has at most M children and M-1 keys.
//   - Each non-root internal node has at least ceil(M/2) children.
//   - All leaves are at the same depth.
//   - The root has at least 2 children (if it is not a leaf).
//
// This class stores key-value pairs in all nodes (not just leaves).
// Keys are kept in sorted order within each node.
//
// Template parameters:
//   K - Key type (must support < and == operators)
//   V - Value type
template <typename K, typename V>
class BTreeMap {
 public:
  // Construct an empty B-tree map with the given order.
  // Order must be at least 3.
  explicit BTreeMap(int order = 4);

  // Destructor: free all allocated nodes.
  ~BTreeMap();

  // Insert a key-value pair. If the key already exists, update its value.
  void Put(const K& key, const V& value);

  // Return a reference to the value associated with key.
  // Throws std::runtime_error if key is not found.
  V& Get(const K& key);
  const V& Get(const K& key) const;

  // Return true if the key exists in the map.
  bool ContainsKey(const K& key) const;

  // Return the number of key-value pairs in the map.
  size_t Size() const;

  // Return all keys in sorted (ascending) order via in-order traversal.
  std::vector<K> Keys() const;

  // Disallow copy and assignment.
  BTreeMap(const BTreeMap&) = delete;
  BTreeMap& operator=(const BTreeMap&) = delete;

  // Allow move construction and assignment.
  BTreeMap(BTreeMap&& other) noexcept;
  BTreeMap& operator=(BTreeMap&& other) noexcept;

 private:
  struct Node {
    std::vector<K> keys;          // Keys stored in this node
    std::vector<V> values;        // Values corresponding to each key
    std::vector<Node*> children;  // Child pointers (empty if leaf)
    bool is_leaf;                 // True if this is a leaf node

    explicit Node(bool leaf) : is_leaf(leaf) {
    }

    // Return true if this node is full (has M-1 keys).
    bool IsFull(int order) const {
      return static_cast<int>(keys.size()) >= order - 1;
    }
  };

  int order_;    // Maximum number of children per node (M)
  Node* root_;   // Root of the B-tree (nullptr if empty)
  size_t size_;  // Number of key-value pairs

  // Search for key starting from the given node.
  // Returns a pointer to the node containing the key, or nullptr if not found.
  // Sets idx to the index of the key within that node's keys vector.
  Node* Search(Node* node, const K& key, int& idx) const;

  // Split the i-th child of parent, which must be full (has M-1 keys).
  // The median key moves up to parent, and the right half becomes a new node.
  void SplitChild(Node* parent, int i);

  // Insert key-value into a node that is guaranteed to be non-full.
  // Uses top-down splitting: if a child is full, split it before descending.
  void InsertNonFull(Node* node, const K& key, const V& value);

  // Collect all keys in sorted order via in-order traversal starting at node.
  void InOrderKeys(const Node* node, std::vector<K>& result) const;

  // Recursively free all nodes in the subtree rooted at node.
  void DestroyTree(Node* node);
};

// ===========================================================================
// ===========================================================================

template <typename K, typename V>
BTreeMap<K, V>::BTreeMap(int order) : order_(order), root_(nullptr), size_(0) {
}

template <typename K, typename V>
BTreeMap<K, V>::~BTreeMap() {
  DestroyTree(root_);
}

template <typename K, typename V>
BTreeMap<K, V>::BTreeMap(BTreeMap&& other) noexcept
    : order_(other.order_), root_(other.root_), size_(other.size_) {
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename K, typename V>
BTreeMap<K, V>& BTreeMap<K, V>::operator=(BTreeMap&& other) noexcept {
  if (this != &other) {
    DestroyTree(root_);
    order_ = other.order_;
    root_ = other.root_;
    size_ = other.size_;
    other.root_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename K, typename V>
void BTreeMap<K, V>::DestroyTree(Node* node) {
  if (node == nullptr)
    return;
  for (Node* child : node->children) {
    DestroyTree(child);
  }
  delete node;
}

template <typename K, typename V>
// 1. Find position i in node->keys where key would fit
// 2. If keys[i] == key, set idx = i and return node
// 3. If node is a leaf, return nullptr (not found)
// 4. Otherwise, recurse into children[i]
typename BTreeMap<K, V>::Node* BTreeMap<K, V>::Search(Node* node, const K& key,
                                                      int& idx) const {
  if (node == nullptr)
    return nullptr;
  size_t i = 0;
  while (i < node->keys.size() && node->keys[i] < key)
    i++;
  if (i < node->keys.size() && node->keys[i] == key) {
    idx = static_cast<int>(i);
    return node;
  }
  if (node->is_leaf)
    return nullptr;
  return Search(node->children[i], key, idx);
}

template <typename K, typename V>
void BTreeMap<K, V>::SplitChild(Node* parent, int i) {
  Node* child = parent->children[i];

  // 1. Create a new node for the right half
  Node* right = new Node(child->is_leaf);

  // 2. Find the median index: mid = (order_ - 1) / 2
  int mid = (order_ - 1) / 2;

  // 3. Move keys[mid+1..end] and values[mid+1..end] to the new node
  right->keys.assign(child->keys.begin() + mid + 1, child->keys.end());
  right->values.assign(child->values.begin() + mid + 1, child->values.end());

  // 4. If not a leaf, move children[mid+1..end] to the new node
  if (!child->is_leaf) {
    right->children.assign(child->children.begin() + mid + 1,
                           child->children.end());
    child->children.erase(child->children.begin() + mid + 1,
                          child->children.end());
  }

  // 5. Insert the median key/value into parent at position i
  parent->keys.insert(parent->keys.begin() + i, child->keys[mid]);
  parent->values.insert(parent->values.begin() + i, child->values[mid]);

  // 6. Insert the new node into parent->children at position i+1
  parent->children.insert(parent->children.begin() + i + 1, right);

  // 7. Remove the moved keys/values/children from the original child
  child->keys.erase(child->keys.begin() + mid, child->keys.end());
  child->values.erase(child->values.begin() + mid, child->values.end());
}

template <typename K, typename V>
void BTreeMap<K, V>::InsertNonFull(Node* node, const K& key, const V& value) {
  // 1. Find position i where key should go
  size_t i = 0;
  while (i < node->keys.size() && node->keys[i] < key)
    i++;

  // 2. If key already exists at position i, update the value and return
  if (i < node->keys.size() && node->keys[i] == key) {
    node->values[i] = value;
    return;
  }

  // 3. If node is a leaf, insert key/value at position i
  if (node->is_leaf) {
    node->keys.insert(node->keys.begin() + i, key);
    node->values.insert(node->values.begin() + i, value);
    size_++;
    return;
  }

  // 4. If node is internal:
  //    a. If children[i] is full, split it (SplitChild)
  //    b. After split, determine which child to descend into
  if (node->children[i]->IsFull(order_)) {
    SplitChild(node, static_cast<int>(i));
    //    b. After split, determine which child to descend into
    if (node->keys[i] < key)
      i++;
  }
  //    c. Recurse into the appropriate child
  InsertNonFull(node->children[i], key, value);
}

template <typename K, typename V>
void BTreeMap<K, V>::Put(const K& key, const V& value) {
  // 1. If tree is empty, create a new root leaf node
  if (root_ == nullptr) {
    root_ = new Node(true);
    root_->keys.push_back(key);
    root_->values.push_back(value);
    size_++;
    return;
  }

  // 2. If root is full, create a new root, make old root its child,
  //    split the old root, then call InsertNonFull on new root
  if (root_->IsFull(order_)) {
    Node* new_root = new Node(false);
    new_root->children.push_back(root_);
    root_ = new_root;
    SplitChild(root_, 0);
  }

  // 3. Otherwise, call InsertNonFull on root
  InsertNonFull(root_, key, value);
}

template <typename K, typename V>
V& BTreeMap<K, V>::Get(const K& key) {
  int idx;
  Node* node = Search(root_, key, idx);
  if (node == nullptr)
    throw std::runtime_error("Key not found");
  return node->values[idx];
}

template <typename K, typename V>
const V& BTreeMap<K, V>::Get(const K& key) const {
  int idx;
  Node* node = Search(root_, key, idx);
  if (node == nullptr)
    throw std::runtime_error("Key not found");
  return node->values[idx];
}

template <typename K, typename V>
bool BTreeMap<K, V>::ContainsKey(const K& key) const {
  int idx;
  return Search(root_, key, idx) != nullptr;
}

template <typename K, typename V>
size_t BTreeMap<K, V>::Size() const {
  return size_;
}

template <typename K, typename V>
std::vector<K> BTreeMap<K, V>::Keys() const {
  std::vector<K> result;
  if (root_ != nullptr)
    InOrderKeys(root_, result);
  return result;
}

template <typename K, typename V>
// For an internal node with k keys and k+1 children:
//   traverse child[0], output key[0],
//   traverse child[1], output key[1],
//   ...
//   traverse child[k-1], output key[k-1],
//   traverse child[k]
// For a leaf: simply add all keys to result
void BTreeMap<K, V>::InOrderKeys(const Node* node,
                                 std::vector<K>& result) const {
  if (node->is_leaf) {
    for (const K& k : node->keys)
      result.push_back(k);
    return;
  }
  for (size_t i = 0; i < node->keys.size(); i++) {
    InOrderKeys(node->children[i], result);
    result.push_back(node->keys[i]);
  }
  InOrderKeys(node->children[node->keys.size()], result);
}

#endif  // BTREE_MAP_H_
