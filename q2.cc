#include <iostream>
// You can only use stack_vector.h to implement this queue
#include "stack_vector.h"

template <typename T> class Queue {
private:
  Stack<T> s1, s2;

public:
  void Push(const T &item) { s1.Push(item); }

  T Pop() {
    if (s2.Size() == 0) {
      if (s1.Size() == 0) {
        throw std::out_of_range("Queue is empty");
      }
      while (s1.Size() != 0) {
        s2.Push(s1.Top());
        s1.Pop();
      }
    }
    T val = s2.Top();
    s2.Pop();
    return val;
  }

  size_t Size() { return s1.Size() + s2.Size(); }

  // Answer to Q2:
  // Push() time complexity: O(1)
  // Pop() time complexity: O(1) amortized, O(n) worst case
  // Size() time complexity: O(1)
};

#ifndef NO_MAIN // Only compile main if NO_MAIN is not defined
int main() {
  Queue<int> q1;

  std::vector<int> v{59, 24, 49, 63, 41};
  for (auto i : v) {
    q1.Push(i);
  }
  // print q1
  while (q1.Size() != 0) {
    std::cout << q1.Pop() << ", ";
  }
  std::cout << std::endl;

  return 0;
}
#endif
