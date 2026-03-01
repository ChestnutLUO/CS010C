#ifndef MULTISET_H_
#define MULTISET_H_

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>

template <typename K> class Multiset {
public:
  Multiset() : root_(nullptr), size_(0) {}

  Multiset(const Multiset &other) : root_(nullptr), size_(0) {
    CopyTree(root_, other.root_);
    size_ = other.size_;
  }

  size_t Size() const;
  bool Empty() const;

  void Insert(const K &key);
  void Remove(const K &key);

  bool Contains(const K &key) const;
  size_t Count(const K &key) const;

  const K &Floor(const K &key) const;
  const K &Ceil(const K &key) const;

  const K &Max() const;
  const K &Min() const;

private:
  struct Node {
    K key;
    size_t count;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(const K &k)
        : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  std::unique_ptr<Node> root_;
  size_t size_;

  Node *InsertHelper(std::unique_ptr<Node> &node, const K &key);
  Node *RemoveHelper(std::unique_ptr<Node> &node, const K &key);
  Node *FindMin(Node *node) const;
  Node *FindMax(Node *node) const;
  Node *FindNode(Node *node, const K &key) const;
  Node *FloorHelper(Node *node, const K &key) const;
  Node *CeilHelper(Node *node, const K &key) const;
  void CopyTree(std::unique_ptr<Node> &dest, const std::unique_ptr<Node> &src);
};

template <typename K> size_t Multiset<K>::Size() const { return size_; }

template <typename K> bool Multiset<K>::Empty() const { return size_ == 0; }

template <typename K> void Multiset<K>::Insert(const K &key) {
  InsertHelper(root_, key);
  size_++;
}

template <typename K> void Multiset<K>::Remove(const K &key) {
  if (!Contains(key)) {
    throw std::runtime_error("Invalid key");
  }
  RemoveHelper(root_, key);
  size_--;
}

template <typename K> bool Multiset<K>::Contains(const K &key) const {
  return FindNode(root_.get(), key) != nullptr;
}

template <typename K> size_t Multiset<K>::Count(const K &key) const {
  Node *node = FindNode(root_.get(), key);
  if (node == nullptr) {
    throw std::runtime_error("Invalid key");
  }
  return node->count;
}

template <typename K> const K &Multiset<K>::Floor(const K &key) const {
  if (Empty()) {
    throw std::runtime_error("Empty multiset");
  }
  Node *result = FloorHelper(root_.get(), key);
  if (result == nullptr) {
    throw std::runtime_error("Invalid key");
  }
  return result->key;
}

template <typename K> const K &Multiset<K>::Ceil(const K &key) const {
  if (Empty()) {
    throw std::runtime_error("Empty multiset");
  }
  Node *result = CeilHelper(root_.get(), key);
  if (result == nullptr) {
    throw std::runtime_error("Invalid key");
  }
  return result->key;
}

template <typename K> const K &Multiset<K>::Max() const {
  if (Empty()) {
    throw std::runtime_error("Empty multiset");
  }
  return FindMax(root_.get())->key;
}

template <typename K> const K &Multiset<K>::Min() const {
  if (Empty()) {
    throw std::runtime_error("Empty multiset");
  }
  return FindMin(root_.get())->key;
}

template <typename K>
typename Multiset<K>::Node *
Multiset<K>::InsertHelper(std::unique_ptr<Node> &node, const K &key) {
  if (node == nullptr) {
    node = std::make_unique<Node>(key);
    return node.get();
  }

  if (key < node->key) {
    return InsertHelper(node->left, key);
  } else if (key > node->key) {
    return InsertHelper(node->right, key);
  } else {
    node->count++;
    return node.get();
  }
}

template <typename K>
typename Multiset<K>::Node *
Multiset<K>::RemoveHelper(std::unique_ptr<Node> &node, const K &key) {
  if (node == nullptr) {
    return nullptr;
  }

  if (key < node->key) {
    return RemoveHelper(node->left, key);
  } else if (key > node->key) {
    return RemoveHelper(node->right, key);
  } else {
    if (node->count > 1) {
      node->count--;
      return node.get();
    }

    if (node->left == nullptr) {
      node = std::move(node->right);
      return node.get();
    } else if (node->right == nullptr) {
      node = std::move(node->left);
      return node.get();
    }

    Node *successor = FindMin(node->right.get());
    node->key = successor->key;
    node->count = successor->count;
    successor->count = 1;
    RemoveHelper(node->right, successor->key);
    return node.get();
  }
}

template <typename K>
typename Multiset<K>::Node *Multiset<K>::FindMin(Node *node) const {
  while (node->left != nullptr) {
    node = node->left.get();
  }
  return node;
}

template <typename K>
typename Multiset<K>::Node *Multiset<K>::FindMax(Node *node) const {
  while (node->right != nullptr) {
    node = node->right.get();
  }
  return node;
}

template <typename K>
typename Multiset<K>::Node *Multiset<K>::FindNode(Node *node,
                                                  const K &key) const {
  if (node == nullptr) {
    return nullptr;
  }

  if (key < node->key) {
    return FindNode(node->left.get(), key);
  } else if (key > node->key) {
    return FindNode(node->right.get(), key);
  } else {
    return node;
  }
}

template <typename K>
typename Multiset<K>::Node *Multiset<K>::FloorHelper(Node *node,
                                                     const K &key) const {
  if (node == nullptr) {
    return nullptr;
  }

  if (key == node->key) {
    return node;
  }

  if (key < node->key) {
    return FloorHelper(node->left.get(), key);
  }

  Node *right_floor = FloorHelper(node->right.get(), key);
  return (right_floor != nullptr) ? right_floor : node;
}

template <typename K>
typename Multiset<K>::Node *Multiset<K>::CeilHelper(Node *node,
                                                    const K &key) const {
  if (node == nullptr) {
    return nullptr;
  }

  if (key == node->key) {
    return node;
  }

  if (key > node->key) {
    return CeilHelper(node->right.get(), key);
  }

  Node *left_ceil = CeilHelper(node->left.get(), key);
  return (left_ceil != nullptr) ? left_ceil : node;
}

template <typename K>
void Multiset<K>::CopyTree(std::unique_ptr<Node> &dest,
                           const std::unique_ptr<Node> &src) {
  if (src == nullptr) {
    return;
  }

  dest = std::make_unique<Node>(src->key);
  dest->count = src->count;
  CopyTree(dest->left, src->left);
  CopyTree(dest->right, src->right);
}

#endif //  MULTISET_H_
