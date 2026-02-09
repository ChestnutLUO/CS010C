#include <memory>
#include <utility>
#include <iostream>
#include <stdexcept>

template <typename K>
class BST {
 public:
  // Return whether @key is found in tree
  bool Contains(const K& key);
  // Return max key in tree
  const K& Max();
  // Return min key in tree
  const K& Min();
  // Insert @key in tree
  void Insert(const K &key);
  // Remove @key from tree
  void Remove(const K &key);
  // Print tree in-order
  void Print();
  // Lowest common ancestor
  const K &LCA(const K &key1, const K &key2);
  // Check if tree is BST
  bool CheckBST();

private:
  struct Node {
    K key;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };
  std::unique_ptr<Node> root;

  // Useful recursive helper methods
  bool Contains(Node *crr_node, const K &key);
  bool CheckBST(Node *root, const K *min, const K *max);
  //
  Node *Min(Node *n);
  void Insert(std::unique_ptr<Node> &n, const K &key);
  void Remove(std::unique_ptr<Node> &n, const K &key);
  void Print(Node *n, int level);
};

// TODO: Q2.1
template <typename K> bool BST<K>::Contains(const K &key) {
  if (!root)
    return false;

  return Contains(root.get(), key);
}

template <typename K> bool BST<K>::Contains(Node *crr_node, const K &key) {
  if (crr_node == nullptr)
    return false;

  if (crr_node->key == key)
    return true;

  return (key < crr_node->key) ? Contains(crr_node->left.get(), key)
                               : Contains(crr_node->right.get(), key);
}

template <typename K> const K &BST<K>::LCA(const K &key1, const K &key2) {
  const K lowkey = std::min(key1, key2);
  const K highkey = std::max(key1, key2);
  Node *n = root.get();
  while (n) {
    if (lowkey <= n->key && n->key <= highkey) {
      return n->key;
    } else {
      if (n->key > highkey) {
        n = n->left.get();
      } else {
        n = n->right.get();
      }
    }
  }
  throw std::runtime_error("LCA: keys not found in tree");
}

// TODO: Q2.3
template <typename K> bool BST<K>::CheckBST() {
  return CheckBST(root.get(), nullptr, nullptr);
}

template <typename K> bool BST<K>::CheckBST(Node *root, const K *min, const K *max) {
  if (!root)
    return true;
  if (min && root->key <= *min) {
    return false;
  }
  if (max && root->key >= *max) {
    return false;
  }
  return CheckBST(root->left.get(), min, &root->key) &&
         CheckBST(root->right.get(), &root->key, max);
}

template <typename K> const K &BST<K>::Max(void) {
  Node *n = root.get();
  while (n->right)
    n = n->right.get();
  return n->key;
}

template <typename K> const K &BST<K>::Min(void) {
  return Min(root.get())->key;
}

template <typename K> typename BST<K>::Node *BST<K>::Min(Node *n) {
  if (n->left)
    return Min(n->left.get());
  else
    return n;
}

template <typename K> void BST<K>::Insert(const K &key) { Insert(root, key); }

template <typename K>
void BST<K>::Insert(std::unique_ptr<Node> &n, const K &key) {
  if (!n)
    n = std::unique_ptr<Node>(new Node{key});
  else if (key < n->key)
    Insert(n->left, key);
  else if (key > n->key)
    Insert(n->right, key);
  else
    std::cerr << "Key " << key << " already inserted!\n";
}

template <typename K> void BST<K>::Remove(const K &key) { Remove(root, key); }

template <typename K>
void BST<K>::Remove(std::unique_ptr<Node> &n, const K &key) {
  // Key not found
  if (!n)
    return;

  if (key < n->key) {
    Remove(n->left, key);
  } else if (key > n->key) {
    Remove(n->right, key);
  } else {
    // Found node
    if (n->left && n->right) {
      // Two children: replace with min node in right subtree
      n->key = Min(n->right.get())->key;
      Remove(n->right, n->key);
    } else {
      // Replace with only child or with nullptr
      n = std::move((n->left) ? n->left : n->right);
    }
  }
}

template <typename K> void BST<K>::Print() {
  Print(root.get(), 1);
  std::cout << std::endl;
}

template <typename K> void BST<K>::Print(Node *n, int level) {
  if (!n)
    return;

  Print(n->left.get(), level + 1);
  std::cout << n->key << " [" << level << "] ";
  Print(n->right.get(), level + 1);
}
