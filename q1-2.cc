#ifndef NO_MAIN
#include <iostream>
#include "stack_vector.h"
#else
#include <iostream>
#endif

template <typename T>

void DeleteMiddleElement(Stack<T> &s, unsigned int n, unsigned int curr = 0) {

  if (s.Size() == 0)
    return;

  T temp = s.Top();
  s.Pop();

  if (curr == n - 1 - n / 2) {
    return;
  }

  DeleteMiddleElement(s, n, curr + 1);

  s.Push(temp);

  // Answer to Q1.2:
  // time Complexity: O(n)
  // space Complexity: O(n)
}

#ifndef NO_MAIN // Only compile main if NO_MAIN is not defined
int main() {
  Stack<int> s1;

  std::vector<int> v{59, 24, 49, 63, 41};
  for (auto i : v)
    s1.Push(i);

  // remove middle item (49)
  DeleteMiddleElement(s1, s1.Size());

  // print s1
  while (s1.Size() != 0) {
    std::cout << s1.Top() << ", ";
    s1.Pop();
  }
  std::cout << std::endl;

  return 0;
}
#endif
