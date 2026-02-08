#include <iostream>
#include <queue>
#include <stack>
#include <utility>

#include "bt.h"

// Make a type alias
using Node = BinaryTree<char>::Node;

// TODO: Q1.1
void PreorderIter(Node *root) {
  if (!root)
    return;
  std::stack<Node *> s;
  s.push(root);
  while (!s.empty()) {
    Node *temp = s.top();
    s.pop();
    if (temp) {
      std::cout << temp->item << ' ';
      if (temp->right) {
        s.push(temp->right.get());
      }
      if (temp->left) {
        s.push(temp->left.get());
      }
    }
  }
}

// TODO: Q1.2
void LevelIter(Node *root) {
  if (!root)
    return;
  std::queue<Node *> q;
  q.push(root);
  while (!q.empty()) {
    Node *temp = q.front();
    q.pop();
    if (temp) {
      std::cout << temp->item << ' ';
      if (temp->left) {
        q.push(temp->left.get());
      }
      if (temp->right) {
        q.push(temp->right.get());
      }
    }
  }
}

#ifndef NO_MAIN // Only compile main if NO_MAIN is not defined
int main() {
  // Statically build a binary tree
  std::unique_ptr<Node> nj(new Node{'j'});
  std::unique_ptr<Node> ni(new Node{'i'});
  std::unique_ptr<Node> nh(new Node{'h'});
  std::unique_ptr<Node> ng(new Node{'g'});
  std::unique_ptr<Node> nf(new Node{'f', std::move(nj)});
  std::unique_ptr<Node> ne(new Node{'e'});
  std::unique_ptr<Node> nd(new Node{'d', std::move(nh), std::move(ni)});
  std::unique_ptr<Node> nc(new Node{'c', std::move(nf), std::move(ng)});
  std::unique_ptr<Node> nb(new Node{'b', std::move(nd), std::move(ne)});
  std::unique_ptr<Node> na(new Node{'a', std::move(nb), std::move(nc)});
  BinaryTree<char> bin_tree{std::move(na)};

  std::cout << "Iterative pre-order: \n";
  PreorderIter(bin_tree.root.get());
  std::cout << std::endl;

  std::cout << "Iterative level-order: \n";
  LevelIter(bin_tree.root.get());
  std::cout << std::endl;

  return 0;
}
#endif
