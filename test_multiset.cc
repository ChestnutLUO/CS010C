#include <gtest/gtest.h>

#include "multiset.h"

TEST(Multiset, Empty) {
  Multiset<int> mset;

  EXPECT_EQ(mset.Empty(), true);
  EXPECT_EQ(mset.Size(), 0);
  EXPECT_THROW(mset.Count(42), std::exception);
}

TEST(Multiset, OneKey) {
  Multiset<int> mset;

  mset.Insert(23);
  mset.Insert(42);
  mset.Insert(42);
  EXPECT_EQ(mset.Empty(), false);
  EXPECT_EQ(mset.Size(), 3);
  EXPECT_EQ(mset.Min(), 23);
  EXPECT_EQ(mset.Max(), 42);
  EXPECT_EQ(mset.Count(42), 2);
}

TEST(Multiset, Remove) {
  Multiset<int> mset;
  mset.Insert(10);
  mset.Insert(5);
  mset.Insert(15);
  mset.Insert(10);

  EXPECT_EQ(mset.Size(), 4);
  EXPECT_EQ(mset.Count(10), 2);

  mset.Remove(10);
  EXPECT_EQ(mset.Size(), 3);
  EXPECT_EQ(mset.Count(10), 1);

  mset.Remove(10);
  EXPECT_EQ(mset.Size(), 2);
  EXPECT_THROW(mset.Count(10), std::exception);
  EXPECT_THROW(mset.Remove(10), std::exception);
}

TEST(Multiset, Contains) {
  Multiset<int> mset;
  mset.Insert(42);
  mset.Insert(23);

  EXPECT_TRUE(mset.Contains(42));
  EXPECT_TRUE(mset.Contains(23));
  EXPECT_FALSE(mset.Contains(100));
}

TEST(Multiset, MinMax) {
  Multiset<int> mset;

  EXPECT_THROW(mset.Min(), std::exception);
  EXPECT_THROW(mset.Max(), std::exception);

  mset.Insert(50);
  mset.Insert(30);
  mset.Insert(70);
  mset.Insert(20);
  mset.Insert(40);

  EXPECT_EQ(mset.Min(), 20);
  EXPECT_EQ(mset.Max(), 70);
}

TEST(Multiset, Floor) {
  Multiset<int> mset;

  EXPECT_THROW(mset.Floor(10), std::exception);

  mset.Insert(10);
  mset.Insert(20);
  mset.Insert(30);
  mset.Insert(40);

  EXPECT_EQ(mset.Floor(25), 20);
  EXPECT_EQ(mset.Floor(30), 30);
  EXPECT_EQ(mset.Floor(50), 40);
  EXPECT_THROW(mset.Floor(5), std::exception);
}

TEST(Multiset, Ceil) {
  Multiset<int> mset;

  EXPECT_THROW(mset.Ceil(10), std::exception);

  mset.Insert(10);
  mset.Insert(20);
  mset.Insert(30);
  mset.Insert(40);

  EXPECT_EQ(mset.Ceil(25), 30);
  EXPECT_EQ(mset.Ceil(30), 30);
  EXPECT_EQ(mset.Ceil(5), 10);
  EXPECT_THROW(mset.Ceil(50), std::exception);
}

TEST(Multiset, DuplicateHandling) {
  Multiset<int> mset;

  for (int i = 0; i < 5; i++) {
    mset.Insert(100);
  }

  EXPECT_EQ(mset.Size(), 5);
  EXPECT_EQ(mset.Count(100), 5);
  EXPECT_EQ(mset.Min(), 100);
  EXPECT_EQ(mset.Max(), 100);

  mset.Remove(100);
  EXPECT_EQ(mset.Count(100), 4);
  EXPECT_EQ(mset.Size(), 4);
}

TEST(Multiset, ComplexTree) {
  Multiset<int> mset;

  mset.Insert(50);
  mset.Insert(30);
  mset.Insert(70);
  mset.Insert(20);
  mset.Insert(40);
  mset.Insert(60);
  mset.Insert(80);
  mset.Insert(30);

  EXPECT_EQ(mset.Size(), 8);
  EXPECT_EQ(mset.Count(30), 2);
  EXPECT_EQ(mset.Min(), 20);
  EXPECT_EQ(mset.Max(), 80);

  EXPECT_EQ(mset.Floor(35), 30);
  EXPECT_EQ(mset.Ceil(35), 40);
  EXPECT_EQ(mset.Floor(65), 60);
  EXPECT_EQ(mset.Ceil(65), 70);
}

TEST(Multiset, RemoveWithChildren) {
  Multiset<int> mset;

  mset.Insert(50);
  mset.Insert(30);
  mset.Insert(70);
  mset.Insert(20);
  mset.Insert(40);
  mset.Insert(60);
  mset.Insert(80);

  mset.Remove(50);
  EXPECT_EQ(mset.Size(), 6);
  EXPECT_FALSE(mset.Contains(50));
  EXPECT_EQ(mset.Min(), 20);
  EXPECT_EQ(mset.Max(), 80);
}
