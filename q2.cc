#include <iostream>
// You can only use stack_vector.h to implement this queue
#include "stack_vector.h"

template<typename T>
class Queue {
 private:
        // TODO: Define private members for your queue

 public:
        void Push(const T &item) {
            // TODO: Push to the queue

        }

        T Pop() {
            // TODO: Pop from the queue 

        }

        size_t Size() {
            // TODO: Return the size of the queue

        }
};

#ifndef NO_MAIN  // Only compile main if NO_MAIN is not defined
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
