#ifndef CUCKOO_HASHING_H
#define CUCKOO_HASHING_H

#include <array>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>

template <typename K>
class CuckooHashing {

    public:
        // Check if @key exists in one of the two hash tables
        bool Contains(const K& key);
        // Insert @key into any one of the hash tables
        void Insert(const K& key);
        // Remove @key from one of the tables if it exists
        void Remove(const K& key);
        // Print hashtable's contents
        void PrintTable();

    private:
        // TODO: Q 1.1 - Define Node structure to hold key and taken status

        // TODO: Q 1.1 - Declare two hash tables with initial capacity
        // Hint: Use std::array<std::vector<Node>, 2> for two tables
        // Initialize each table with init_capacity size
        // Initialize cur_size to 0

        // Hash function for first table
        size_t Hash1(const K& key);

        // Hash function for second table
        size_t Hash2(const K& key);

        // Resize to new capacity
        void Resize(size_t capacity);

        // Recursively insert @key to table @id (either 0 or 1)
        // TODO: Q 2.3 - Implement InsertRecur
        // Note: depth parameter is used to prevent infinite loops
        void InsertRecur(const K& key, size_t id, int depth = 0);
};

// TODO: Q 1.2 - Implement Hash1
template <typename K>
size_t CuckooHashing<K>::Hash1(const K& key) {
    // Implement your first hash function here
    // Suggestion: h(k) = k mod size
    return 0;
}

// TODO: Q 1.2 - Implement Hash2
template <typename K>
size_t CuckooHashing<K>::Hash2(const K& key) {
    // Implement your second hash function here
    // Suggestion: h(k) = (k/size) mod size
    return 0;
}

// TODO: Q 2.1 - Implement Contains
template <typename K>
bool CuckooHashing<K>::Contains(const K& key) {
    // Check if the key exists in one of the two hash tables
    return false;
}

// TODO: Q 2.3 - Implement InsertRecur
template <typename K>
void CuckooHashing<K>::InsertRecur(const K& key, size_t id, int depth) {
    // Recursively insert key into table id
    // Handle collision by swapping to the other table
    // IMPORTANT: Check depth to prevent infinite loops!
    // If depth exceeds a threshold (e.g., 2 * table_size), trigger Resize
}

// TODO: Q 2.2 - Implement Insert
template <typename K>
void CuckooHashing<K>::Insert(const K& key) {
    // Check if key already exists (skip if it does)
    // Update size
    // TODO: Q 2.4 - Check for resize
    // Always try to insert to the first hash table
}

// TODO: Q 2.4 - Implement Resize
template <typename K>
void CuckooHashing<K>::Resize(size_t capacity) {
    // Double the size of hashtables and rehash the entire collection
}

// TODO: Q 2.5 - Implement Remove
template <typename K>
void CuckooHashing<K>::Remove(const K& key) {
    // Find key and clear it from the table
}

template <typename K>
void CuckooHashing<K>::PrintTable() {
    for (int i = 0; i < 2; i++) {
        std::cout << "Hash table #" << i << std::endl;

        for (auto &k : ht[i]) {
            if (k.taken)
                std::cout << "["
                        << std::setfill('0') << std::setw(3) << k.key
                        << "]";
            else
                std::cout << "[---]";
        }

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

#endif
