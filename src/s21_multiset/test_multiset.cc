#include <gtest/gtest.h>
#include "s21_multiset.h"
#include <iostream>

using namespace std;

namespace constructors_suite {
    TEST(constructors, empty_constructor) {
        s21::multiset<double> multi;
        ASSERT_EQ(multi.size(), 0);
    }
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
