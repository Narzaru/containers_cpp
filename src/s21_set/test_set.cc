#include <gtest/gtest.h>
#include "s21_set.h"
#include <iostream>

using namespace std;

namespace constructors_suite {
    TEST(constructors, empty_constructor) {
        s21::set<double> set;
        ASSERT_EQ(set.size(), 0);
    }

    TEST(constructors, initializer_list) {
        s21::set<double> set{1, 2, 3, 4, 5};
        ASSERT_EQ(set.size(), 5);
        auto it = set.begin();
        for (int i = 1; i <= 5; i++) {
          ASSERT_EQ(i, *it);
          ++it;
        }
    }

    TEST(constructors, copy_constructor) {
        s21::set<double> origin{1, 2, 3, 4, 5};
        s21::set<double> copy(origin);
        ASSERT_EQ(copy.size(), origin.size());
        auto it_origin = origin.begin();
        for (auto it_copy = copy.begin(); it_copy != copy.end(); ++it_copy) {
          ASSERT_EQ(*it_origin, *it_copy);
          ++it_origin;
        }
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
      set.insert(1);
      set.insert(10);
      set.insert(12);
      set.insert(15);
      set.insert(20);
      

      std::pair<s21::set<double>::iterator, bool> pair(set.insert(15));
      double first = *pair.first;
      s21::set<double>::iterator begin = set.begin();
      ASSERT_EQ(*begin, 1);
      ASSERT_EQ(first, 15);
      ASSERT_EQ(pair.second, false);
      ASSERT_EQ(set.size(), 5);

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

      s21::set<double>::iterator it = set.find(15);
      set.erase(it);
      ASSERT_FALSE(set.contains(15));
      ASSERT_EQ(set.size(), 4);
      // for (it = set.begin(); it != set.end(); ++it) {
      //   cout << *it << endl;
      // }
      // ++it;
      //   cout << *it << endl;
      // ++it;
      //   cout << *it << endl;
      // ++it;
      //   cout << *it << endl;
      // ++it;
      //   cout << *it << endl;

    // for (it = set.end(); it != set.begin(); --it) {
    //     cout << *it << endl;
    // }
    // cout << *it << endl;
    // --it;
    // cout << *it << endl;
    // --it;
    // cout << *it << endl;
    // --it;
    // cout << *it << endl;
    // --it;
    // cout << *it << endl;
    // --it;

    }

    TEST(modifiers, swap) {
        s21::set<double> set1, set2;
        set1.insert(5);
        set2.insert(6);
        set2.insert(7);
        set1.swap(set2);
        ASSERT_EQ(set1.size(), 2);
        ASSERT_EQ(set2.size(), 1);
        ASSERT_TRUE(set1.contains(6));
        ASSERT_TRUE(set1.contains(7));
        ASSERT_TRUE(set2.contains(5));
    }

    TEST(modifiers, merge) {
        s21::set<double> set1, set2;
        set1.insert(5);
        set2.insert(6);
        set2.insert(7);
        set1.merge(set2);
        ASSERT_EQ(set1.size(), 3);
        ASSERT_EQ(set2.size(), 2);
        ASSERT_TRUE(set1.contains(6));
        ASSERT_TRUE(set1.contains(7));
        ASSERT_TRUE(set2.contains(6));
    }
}

int main(int argc, char *argv[]) {
  s21::set<double> set;

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
