#ifndef SPLAYTREE_H_
#define SPLAYTREE_H_

#include <iostream>

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
  Node *find(const K &key);

public:
  // public API
  bool Contains(const K &key);
  void Insert(const K &key);
  void Print();
};

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
