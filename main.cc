#include <vector>

#include "splaytree.h"

int main() {
    std::vector<int> v{42, 15, 54, 23};
    SplayTree<int> set;

    // insertion of keys
    for (auto i : v) {
        set.Insert(i);
        set.Print();
        std::cout << std::endl;
    }

    // test contains
    std::cout << std::endl;
    std::cout << "Contains 42: " << set.Contains(42) << std::endl;
    set.Print();
    std::cout << std::endl;

    std::cout << "Contains 100: " << set.Contains(100) << std::endl;
    set.Print();
    std::cout << std::endl;

    return 0;
}
