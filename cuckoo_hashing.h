#ifndef CUCKOO_HASHING_H
#define CUCKOO_HASHING_H

#include <array>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename K> class CuckooHashing {

public:
  // Check if @key exists in one of the two hash tables
  CuckooHashing() : cur_size() {
    ht[0].resize(init_capacity);
    ht[1].resize(init_capacity);
  }
  bool Contains(const K &key);
  // Insert @key into any one of the hash tables
  void Insert(const K &key);
  // Remove @key from one of the tables if it exists
  void Remove(const K &key);
  // Print hashtable's contents
  void PrintTable();

private:
  // TODO: Q 1.1 - Define Node structure to hold key and taken status
  struct Node {
    K key;
    bool taken;
    Node() : key(K()), taken(false) {}
  };

  static const size_t init_capacity = 7;
  std::array<std::vector<Node>, 2> ht;
  size_t cur_size;

  // Hash function for first table
  size_t Hash1(const K &key);

  // Hash function for second table
  size_t Hash2(const K &key);

  void Resize(size_t capacity);

  // TODO: Q 2.3 - Implement InsertRecur
  // Note: depth parameter is used to prevent infinite loops
  void InsertRecur(const K &key, size_t id, size_t depth = 0);
};

// TODO: Q 1.2 - Implement Hash1
template <typename K> size_t CuckooHashing<K>::Hash1(const K &key) {
  return key % ht[0].size();
}

// TODO: Q 1.2 - Implement Hash2
template <typename K> size_t CuckooHashing<K>::Hash2(const K &key) {
  return (key / ht[1].size()) % ht[1].size();
}

// TODO: Q 2.1 - Implement Contains
template <typename K> bool CuckooHashing<K>::Contains(const K &key) {
  size_t index1 = Hash1(key);
  size_t index2 = Hash2(key);

  if (ht[0][index1].taken && ht[0][index1].key == key)
    return true;
  if (ht[1][index2].taken && ht[1][index2].key == key)
    return true;

  return false;
}

// TODO: Q 2.3 - Implement InsertRecur
template <typename K>
void CuckooHashing<K>::InsertRecur(const K &key, size_t id, size_t depth) {
  if (depth > 2 * ht[0].size()) {
    Resize(2 * ht[0].size());
    Insert(key);
    return;
  }

  size_t index = (id == 0) ? Hash1(key) : Hash2(key);

  if (!ht[id][index].taken) {
    ht[id][index].key = key;
    ht[id][index].taken = true;
    return;
  }

  K old_key = ht[id][index].key;
  ht[id][index].key = key;

  InsertRecur(old_key, 1 - id, depth + 1);
}

// TODO: Q 2.2 - Implement Insert
template <typename K> void CuckooHashing<K>::Insert(const K &key) {
  if (Contains(key))
    return;

  cur_size++;

  if (cur_size * 1.0 / ht[0].size() > 0.5) {
    Resize(2 * ht[0].size());
  }

  InsertRecur(key, 0, 0);
}

// TODO: Q 2.4 - Implement Resize
template <typename K> void CuckooHashing<K>::Resize(size_t capacity) {
  std::array<std::vector<Node>, 2> old_ht = ht;

  ht[0].clear();
  ht[1].clear();
  ht[0].resize(capacity);
  ht[1].resize(capacity);
  cur_size = 0;

  for (int i = 0; i < 2; i++) {
    for (const auto &node : old_ht[i]) {
      if (node.taken) {
        Insert(node.key);
      }
    }
  }
}

// TODO: Q 2.5 - Implement Remove
template <typename K> void CuckooHashing<K>::Remove(const K &key) {
  size_t index1 = Hash1(key);
  size_t index2 = Hash2(key);

  if (ht[0][index1].taken && ht[0][index1].key == key) {
    ht[0][index1].taken = false;
    cur_size--;
    return;
  }

  if (ht[1][index2].taken && ht[1][index2].key == key) {
    ht[1][index2].taken = false;
    cur_size--;
    return;
  }
}

template <typename K> void CuckooHashing<K>::PrintTable() {
  for (int i = 0; i < 2; i++) {
    std::cout << "Hash table #" << i << std::endl;

    for (auto &k : ht[i]) {
      if (k.taken)
        std::cout << "[" << std::setfill('0') << std::setw(3) << k.key << "]";
      else
        std::cout << "[---]";
    }

    std::cout << std::endl;
  }
  std::cout << std::endl;
}

#endif
