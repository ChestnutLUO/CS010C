#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "bst.h"

// Tester
int main() {
  std::vector<int> keys{15, 7, 22, 5, 9, 18, 25, 8, 12};

  BST<int> bst;
  for (auto i : keys)
    bst.Insert(i);

  // Q2.1
  std::cout << "Tree contains 22? "
      << bst.Contains(22) << "\n";
  std::cout << "Tree contains 23? "
      << bst.Contains(23) << "\n";

  //Q2.2
  std::cout << "bst.LCA(8, 12) = " << bst.LCA(8, 12) << "\n";
  std::cout << "bst.LCA(8, 7) = " << bst.LCA(8, 7) << "\n";
  std::cout << "bst.LCA(25, 12) = " << bst.LCA(25, 12) << "\n";

  //Q2.3
  std::cout << "CheckBST: " << bst.CheckBST() << "\n";

  return 0;
}
