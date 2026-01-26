#include <gtest/gtest.h>  // there may be a red line under this
// if you do not have gtest installed locally.
// if you are using the cs010c container,
// you may disregard any errors from the previous line on local
#include "list_doubly_linked.h"

TEST(List, List) {
  ListDoublyLinked<int> l;
  ASSERT_EQ(l.Size(), 0);
}

TEST(List, Insert) {
  ListDoublyLinked<int> l;
  l.Insert(10, 0);
  ASSERT_EQ(l.Size(), 1);
  ASSERT_EQ(l.Get(0), 10);

  l.Insert(20, 1);
  ASSERT_EQ(l.Size(), 2);
  ASSERT_EQ(l.Get(1), 20);

  l.Insert(5, 0);
  ASSERT_EQ(l.Size(), 3);
  ASSERT_EQ(l.Get(0), 5);
}

TEST(List, Remove) {
  ListDoublyLinked<int> l;
  l.Insert(10, 0);
  l.Insert(20, 1);
  l.Insert(30, 2);

  l.Remove(1);
  ASSERT_EQ(l.Size(), 2);
  ASSERT_EQ(l.Get(1), 30);

  l.Remove(0);
  ASSERT_EQ(l.Size(), 1);
  ASSERT_EQ(l.Get(0), 30);
}

TEST(List, Find) {
  ListDoublyLinked<int> l;
  l.Insert(10, 0);
  l.Insert(20, 1);

  ASSERT_EQ(l.Find(10), 0);
  ASSERT_EQ(l.Find(20), 1);
  ASSERT_EQ(l.Find(30), -1);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
