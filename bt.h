#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <memory>

template <typename T>
class BinaryTree {
 public:
  struct Node{
    T item;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };
  std::unique_ptr<Node> root;
};

#endif  // BINARY_TREE_H_
