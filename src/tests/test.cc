#include <gtest/gtest.h>

// !The header will be removed along
// with the change to the Makefile
#include "vector.cc"

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
