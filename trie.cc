#include <iostream>
#include <string>

#include "trie.h"

int main() {
  Trie trie;

  trie.Insert("apple");
  trie.Insert("app");
  trie.Insert("bat");
  trie.Insert("bath");
  trie.Insert("banana");
  trie.Insert("badapple");

  std::cout << std::boolalpha;
  std::cout << "Search app: " << trie.Search("app") << '\n';
  std::cout << "Search apple: " << trie.Search("apple") << '\n';
  std::cout << "Search apples: " << trie.Search("apples") << '\n';
  std::cout << "Search ba: " << trie.Search("ba") << '\n';

  std::cout << "StartsWith ap: " << trie.StartsWith("ap") << '\n';
  std::cout << "StartsWith bat: " << trie.StartsWith("bat") << '\n';
  std::cout << "StartsWith ban: " << trie.StartsWith("ban") << '\n';
  std::cout << "StartsWithcat: " << trie.StartsWith("cat") << '\n';

  return 0;
}
