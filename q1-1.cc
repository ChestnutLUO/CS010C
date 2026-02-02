#include <iostream>

#include "stack_vector.h"

template <typename T> Stack<T> Sort(Stack<T> &s1) {
  // TODO: Sort the stack s1 and return the sorted stack
  Stack<T> s2;
  T temp;
  while (!s1.empty()) {
    temp = s1.Top();
    s1.Pop();
    while (!s2.empty() && (temp > s2.Top())) {
      s1.Push(s2.Top());
      s2.Pop();
    }
    s2.Push(temp);
  }
  return s2;
}

#ifndef NO_MAIN // Only compile main if NO_MAIN is not defined
int main() {
  Stack<int> s1;

  std::vector<int> v{44, 12, 59, 41};
  for (auto i : v)
    s1.Push(i);

  // sort
  Stack<int> s2 = Sort(s1);

  // print s2
  while (s2.Size() != 0) {
    std::cout << s2.Top() << ", ";
    s2.Pop();
  }
  std::cout << std::endl;

  return 0;
}
#endif
