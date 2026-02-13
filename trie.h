#ifndef TRIE_H_
#define TRIE_H_

#include <array>
#include <string>

class TrieNode {
    public:
        TrieNode();  // Constructor to initialize members
        TrieNode* Get(const char c);
        void Put(const char c, TrieNode *n);
        bool ContainsKey(const char c);
        void SetEnd();
        bool IsEnd();

    private:
        // TODO: Add private members
        // Hint: You need to store children nodes and track if this is the end of a word

        // TODO: Add helper function(s)
        // Hint: Create a function that transforms an ASCII character into an integer 0-25
};

// TODO: Implementations of TrieNode methods


class Trie {
    public:
        // Inserts @word to the trie
        void Insert(const std::string &word);
        // Returns whether @word is found in the trie
        bool Search(const std::string &word);
        // Returns whether the trie contains a word that begins with @prefix
        bool StartsWith(const std::string &prefix);
    private:
        // TODO: Add root node

        // TODO: Add helper function to search against a certain prefix
        // Hint: This should be used by both Search() and StartsWith()
};

// TODO: Implementations of Trie methods


// Q4.1 Trie Usage
// TODO: Answer the question about Trie usage for other languages
// Your answer: 

#endif // TRIE_H_
