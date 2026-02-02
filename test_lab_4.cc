#include <gtest/gtest.h>
#include "stack_vector.h"
#define NO_MAIN  // This prevents main() from being included
#include "q1-1.cc"
#include "q1-2.cc"
#include "q2.cc"
#undef NO_MAIN

// Test Suite Example for Q1.1
TEST(StackSortTest, BasicSort) {
    Stack<int> s;
    s.Push(3);
    s.Push(1);
    s.Push(2);

    Stack<int> sorted = Sort(s);

    EXPECT_EQ(sorted.Top(), 1);  // Smallest on top
    sorted.Pop();
    EXPECT_EQ(sorted.Top(), 2);
    // Add more assertions...
}

// Add more tests suites for Q1.1, Q1.2, and Q2

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
