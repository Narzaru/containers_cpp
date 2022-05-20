#include <gtest/gtest.h>
#include "s21_set.h"
#include <iostream>

using namespace std;

namespace constructors_suite {
    TEST(constructors, empty_constructor) {
        s21::set<double> set;
        ASSERT_EQ(set.size(), 0);
    }

    TEST(insert, empty_constructor) {
      s21::set<double> set;
      std::pair<s21::set<double>::iterator, bool> pair(set.insert(10));
      ASSERT_EQ(set.size(), 1);
      double first = *pair.first;
      ASSERT_EQ(first, 10);
      ASSERT_EQ(pair.second, true);

    }

    TEST(insert, insert_several_nodes) {
      s21::set<double> set;
      set.insert(10);
      set.insert(20);
      set.insert(1);
      set.insert(15);

      std::pair<s21::set<double>::iterator, bool> pair(set.insert(15));
      double first = *pair.first;
      s21::set<double>::iterator begin = set.begin();
      ASSERT_EQ(*begin, 1);
      ASSERT_EQ(first, 15);
      ASSERT_EQ(pair.second, false);
      ASSERT_EQ(set.size(), 4);

      s21::set<double>::iterator number = set.find(16);
      ASSERT_EQ(number.itr, number.end);
      number = set.find(15);
      ASSERT_EQ(*number, 15);
      number = set.find(14);
      ASSERT_EQ(number.itr, number.end);

      ASSERT_FALSE(set.contains(21));
      ASSERT_FALSE(set.contains(19));
      ASSERT_TRUE(set.contains(15));
      ASSERT_TRUE(set.contains(1));

      s21::set<double>::iterator it;
      for (it = set.begin(); it != set.end(); ++it) {
        cout << *it << endl;
      }
      ++it;
        cout << *it << endl;
      ++it;
        cout << *it << endl;

    }
}

int main(int argc, char *argv[]) {
  s21::set<double> set;

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
