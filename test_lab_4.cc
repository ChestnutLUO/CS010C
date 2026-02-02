#include "stack_vector.h"
#include <gtest/gtest.h>
#define NO_MAIN
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

  // 1, 2, 3
  EXPECT_EQ(sorted.Top(), 1);
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 2);
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 3);
  sorted.Pop();
  EXPECT_TRUE(sorted.empty());
}

TEST(StackSortTest, EmptyStack) {
  Stack<int> s;
  Stack<int> sorted = Sort(s);
  EXPECT_TRUE(sorted.empty());
}

TEST(StackSortTest, SingleElement) {
  Stack<int> s;
  s.Push(42);
  Stack<int> sorted = Sort(s);
  EXPECT_EQ(sorted.Top(), 42);
  sorted.Pop();
  EXPECT_TRUE(sorted.empty());
}

TEST(StackSortTest, AlreadySorted) {
  Stack<int> s;
  // top is smallest (1)
  s.Push(3);
  s.Push(2);
  s.Push(1);

  Stack<int> sorted = Sort(s);

  EXPECT_EQ(sorted.Top(), 1);
  sorted.Pop();

  EXPECT_EQ(sorted.Top(), 2);
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 3);
  sorted.Pop();
  EXPECT_TRUE(sorted.empty());
}

TEST(StackSortTest, ReverseSorted) {
  Stack<int> s;
  // Push such that top is largest (3)
  s.Push(1);
  s.Push(2);
  s.Push(3);

  Stack<int> sorted = Sort(s);

  EXPECT_EQ(sorted.Top(), 1);
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 2);
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 3);
  sorted.Pop();
  EXPECT_TRUE(sorted.empty());
}

TEST(StackSortTest, Duplicates) {
  Stack<int> s;
  s.Push(2);
  s.Push(1);
  s.Push(2);
  s.Push(1);

  Stack<int> sorted = Sort(s);

  // 1, 1, 2, 2
  EXPECT_EQ(sorted.Top(), 1);
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 1);
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 2);
  sorted.Pop();
  EXPECT_EQ(sorted.Top(), 2);
  sorted.Pop();
  EXPECT_TRUE(sorted.empty());
}

TEST(DeleteMiddleTest, OddSize) {
  Stack<int> s;
  // 59, 24, 49, 63, 41
  // Indices: 0, 1, 2, 3, 4
  s.Push(59);
  s.Push(24);
  s.Push(49);
  s.Push(63);
  s.Push(41);

  DeleteMiddleElement(s, s.Size());

  EXPECT_EQ(s.Top(), 41);
  s.Pop();
  EXPECT_EQ(s.Top(), 63);
  s.Pop();
  EXPECT_EQ(s.Top(), 24);
  s.Pop();
  EXPECT_EQ(s.Top(), 59);
  s.Pop();
  EXPECT_TRUE(s.empty());
}

TEST(DeleteMiddleTest, EvenSize) {
  Stack<int> s;
  // 1, 2, 3, 4 (Bottom -> Top)
  // Size 4. 4/2 = 2. at index 2 is 3.
  // (Indices: 0->1, 1->2, 2->3, 3->4)
  s.Push(1);
  s.Push(2);
  s.Push(3);
  s.Push(4);

  DeleteMiddleElement(s, s.Size());

  // Expected: 4, 2, 1 (Top -> Bottom)
  EXPECT_EQ(s.Top(), 4);
  s.Pop();
  EXPECT_EQ(s.Top(), 2);
  s.Pop();
  EXPECT_EQ(s.Top(), 1);
  s.Pop();
  EXPECT_TRUE(s.empty());
}

TEST(DeleteMiddleTest, SingleElement) {
  Stack<int> s;
  s.Push(10);
  DeleteMiddleElement(s, s.Size());
  EXPECT_TRUE(s.empty());
}

TEST(DeleteMiddleTest, EmptyStack) {
  Stack<int> s;
  DeleteMiddleElement(s, s.Size());
  EXPECT_TRUE(s.empty());
}

// Test Suite for Q2: Queue
TEST(QueueTest, BasicFIFO) {
  Queue<int> q;
  q.Push(1);
  q.Push(2);
  q.Push(3);

  EXPECT_EQ(q.Size(), 3);
  EXPECT_EQ(q.Pop(), 1);
  EXPECT_EQ(q.Pop(), 2);
  EXPECT_EQ(q.Pop(), 3);
  EXPECT_EQ(q.Size(), 0);
}

TEST(QueueTest, InterleavedOps) {
  Queue<int> q;
  q.Push(10);
  q.Push(20);
  EXPECT_EQ(q.Pop(), 10);
  q.Push(30);             // 20, 30
  EXPECT_EQ(q.Pop(), 20);
  EXPECT_EQ(q.Pop(), 30);
  EXPECT_EQ(q.Size(), 0);
}

TEST(QueueTest, EmptyQueueThrows) {
  Queue<int> q;
  EXPECT_THROW(q.Pop(), std::out_of_range);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
