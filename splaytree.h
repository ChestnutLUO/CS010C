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
  void printHelper(Node *n, int level);
  Node *copyTree(Node *n);

 public:
  // public API

  void destruct(Node* c) {
      if(!c)
          return;
      destruct(c->left);
      destruct(c->right);
      delete c;
      return;
  }
  ~SplayTree() {destruct(root);}
  SplayTree() : root(nullptr) {}
  SplayTree(const SplayTree &other) : root(copyTree(other.root)) {}
  SplayTree &operator=(const SplayTree &other) {
    if (this != &other) {
      destruct(root);
      root = copyTree(other.root);
    }
    return *this;
  }
  bool Contains(const K &key);
  void Insert(const K &key);
  void Print();
};

template <typename K> void SplayTree<K>::Rotate(Node *&c, rotate_direction d) {
  Node *s = d ? c->left : c->right;
  d ? (c->left = s->right, s->right = c) : (c->right = s->left, s->left = c);
  c = s;
}

template <typename K> void SplayTree<K>::Splay(Node *&c, const K &key) {
  if (!c || c->key == key)
    return;
  if (c->key < key) {
    if (!c->right)
      return;
    if (c->right->key > key) {
      //  Zig-Zag (right-left): c->right->left
      Splay(c->right->left, key);
      if (c->right->left)
        Rotate(c->right, R);
    } else if (c->right->key < key) {
      //  Zig-Zig (right-right):c->right->right
      Splay(c->right->right, key);
      if (c->right->right)
        Rotate(c->right, L);
    }
    if (c->right) {
      Rotate(c, L);
    }
  } else {
    if (!c->left)
      return;
    if (c->left->key > key) {
      //  Zig-Zig (left-left): c->left->left
      Splay(c->left->left, key);
      if (c->left->left)
        Rotate(c->left, R);
    } else if (c->left->key < key) {
      //  Zig-Zag (left-right): c->left->right
      Splay(c->left->right, key);
      if (c->left->right)
        Rotate(c->left, L);
    }
    if (c->left) {
      Rotate(c, R);
    }
  }
}

// TODO: Implement the Contains method
template <typename K> bool SplayTree<K>::Contains(const K &key) {
  if (!root)
    return false;
  Splay(root, key);
  return root->key == key;
}

// TODO: Implement the Insert method (public version)
template <typename K> void SplayTree<K>::Insert(const K &key) {
  if (!root) {
    root = new Node{key, nullptr, nullptr};
    return;
  }
  Node *curr = root;
  while (true) {
    if (key < curr->key) {
      if (!curr->left) {
        curr->left = new Node{key, nullptr, nullptr};
        break;
      }
      curr = curr->left;
    } else if (key > curr->key) {
      if (!curr->right) {
        curr->right = new Node{key, nullptr, nullptr};
        break;
      }
      curr = curr->right;
    } else {
      return;
    }
  }
  Splay(root, key);
}

// TODO: Implement the Print method
// This should print an in-order traversal of the tree
// in this format: "key1 (level), key2 (level), ..."
// You may use this code: std::cout << key << " (" << level << "), ";
template <typename K> void SplayTree<K>::Print() { printHelper(root, 0); }

template <typename K> void SplayTree<K>::printHelper(Node *n, int level) {
  if (!n)
    return;
  printHelper(n->left, level + 1);
  std::cout << n->key << " (" << level << "), ";
  printHelper(n->right, level + 1);
}

template <typename K>
typename SplayTree<K>::Node *SplayTree<K>::find(const K &key) {
  Node *curr = root;
  while (curr) {
    if (key == curr->key)
      return curr;
    curr = (key < curr->key) ? curr->left : curr->right;
  }
  return nullptr;
}

template <typename K>
typename SplayTree<K>::Node *SplayTree<K>::copyTree(Node *n) {
  if (!n) return nullptr;
  return new Node{n->key, copyTree(n->left), copyTree(n->right)};
}

// TODO: Q2.1 What are the different **splay rotation cases** that must be
// considered? Your answer:

// TODO: Q2.2 Implement RotateLeft and RotateRight

// TODO: Q2.3 Implement Splay

#endif  //  SPLAYTREE_H_
