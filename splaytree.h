#ifndef SPLAYTREE_H_
#define SPLAYTREE_H_

#include <iostream>
#include <typeindex>

enum rotate_direction { L, R };

template <typename K> class SplayTree {
private:
  // TODO: define internal data structure
  struct Node {
    K key;
    Node *left;
    Node *right;
  };
  Node *root;
  // helper methods
  void Splay(Node *&c, const K &key);
  Node *find(const K &key);
  void Rotate(Node *&c, rotate_direction);

public:
  // public API
  bool Contains(const K &key);
  void Insert(const K &key);
  void Print();
};

template <typename K> void SplayTree<K>::Splay(Node *&c, const K &key) {
  if (!c || c->key == key)
    return;
  if (c->key < key) {
    if (!c->right)
      return;
    if (c->right->key > key) {
      // Zig-Zag (right-left): target is in c->right->left
      Splay(c->right->left, key);
      Rotate(c->right, R);
    } else {
      // Zig-Zig (right-right): target is in c->right->right
      Splay(c->right->right, key);
      Rotate(c->right, L);
    }
    if (c->right) {
      Rotate(c, L);
    }
  } else {
    if (!c->left)
      return;
    if (c->left->key > key) {
      // Zig-Zig (left-left): target is in c->left->left
      Splay(c->left->left, key);
      Rotate(c->left, R);
    } else {
      // Zig-Zag (left-right): target is in c->left->right
      Splay(c->left->right, key);
      Rotate(c->left, L);
    }
    if (c->left) {
      Rotate(c, R);
    }
  }
}

// TODO: Implement the Contains method
template <typename K> bool SplayTree<K>::Contains(const K &key) {
  // Your implementation here
  return false;
}

// TODO: Implement the Insert method (public version)
template <typename K> void SplayTree<K>::Insert(const K &key) {
  // Your implementation here
}

// TODO: Implement the Print method
// This should print an in-order traversal of the tree
// in this format: "key1 (level), key2 (level), ..."
// You may use this code: std::cout << key << " (" << level << "), ";
template <typename K> void SplayTree<K>::Print() {
  // Your implementation here
}

template <typename K> SplayTree<K>::Node *SplayTree<K>::find(const K &key) {}

// TODO: Q2.1 What are the different **splay rotation cases** that must be
// considered? Your answer:

// TODO: Q2.2 Implement RotateLeft and RotateRight

// TODO: Q2.3 Implement Splay

#endif // SPLAYTREE_H_
