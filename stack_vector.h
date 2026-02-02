#ifndef STACK_VECTOR_H
#define STACK_VECTOR_H

#include <cstddef>
#include <vector>
#include <stdexcept>

template <typename T> class Stack {
private:
  std::vector<T> _data;

public:
  Stack() = default;
  ~Stack() = default;

  void Push(T in) { _data.push_back(in); }

  T Top() const {
    if (_data.empty()) {
      throw std::out_of_range("Stack is empty");
    }
    return _data.back();
  }

  void Pop() {
    if (_data.empty()) {
      throw std::out_of_range("Stack is empty");
    }
    _data.pop_back();
  }

  bool empty() const { return _data.empty(); }
  size_t Size() const { return _data.size(); }
};

#endif // STACK_VECTOR_H
