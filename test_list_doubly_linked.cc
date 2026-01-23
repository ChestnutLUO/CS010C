#include <gtest/gtest.h> // there may be a red line under this 
// if you do not have gtest installed locally.
// if you are using the cs010c container, 
// you may disregard any errors from the previous line on local 
#include "list_doubly_linked.h"
TEST(List, List) {
  ListDoublyLinked<int> l;
  ASSERT_EQ(l.Size(), 0);

  //... more tests here
  
}
int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS(); 
}