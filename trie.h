#ifndef TRIE_H_
#define TRIE_H_

#include <array>
#include <string>

class TrieNode {
public:
  TrieNode();
  ~TrieNode();
  TrieNode *Get(const char c);
  void Put(const char c, TrieNode *n);
  bool ContainsKey(const char c);
  void SetEnd();
  bool IsEnd();

private:
  std::array<TrieNode *, 26> _data{};
  bool is_end;
  size_t GetIndex(char c) const { return c - 'a'; }
};

TrieNode::TrieNode() : is_end(false) {
  for (size_t i = 0; i < 26; i++) {
    _data[i] = nullptr;
  }
}

TrieNode::~TrieNode() {
  for (TrieNode *child : _data) {
    delete child;
  }
}

TrieNode *TrieNode::Get(const char c) { return _data[GetIndex(c)]; }

void TrieNode::Put(const char c, TrieNode *n) { _data[GetIndex(c)] = n; }

bool TrieNode::ContainsKey(const char c) {
  return _data[GetIndex(c)] != nullptr;
}

void TrieNode::SetEnd() { is_end = true; }

bool TrieNode::IsEnd() { return is_end; }

class Trie {
public:
  Trie();
  ~Trie();
  void Insert(const std::string &word);
  bool Search(const std::string &word);
  bool StartsWith(const std::string &prefix);

private:
  TrieNode *_root;

  TrieNode *SearchPrefix(const std::string &prefix);
};

Trie::Trie() : _root(new TrieNode()) {}

Trie::~Trie() { delete _root; }

void Trie::Insert(const std::string &word) {
  TrieNode *node = _root;
  for (char c : word) {
    if (!node->ContainsKey(c)) {
      node->Put(c, new TrieNode());
    }
    node = node->Get(c);
  }
  node->SetEnd();
}

TrieNode *Trie::SearchPrefix(const std::string &prefix) {
  TrieNode *node = _root;
  for (char c : prefix) {
    if (!node->ContainsKey(c)) {
      return nullptr;
    }
    node = node->Get(c);
  }
  return node;
}

bool Trie::Search(const std::string &word) {
  TrieNode *node = SearchPrefix(word);
  return node != nullptr && node->IsEnd();
}

bool Trie::StartsWith(const std::string &prefix) {
  return SearchPrefix(prefix) != nullptr;
}

// TODO: Answer the question about Trie usage for other languages
// Your answer: It will effect the length of the subnoes index and deep in tree.
// Such as Hindi have longer alphabet will cause it longer. Mongolian long words
// on average cause trie tree more deep in average;

#endif // TRIE_H_
