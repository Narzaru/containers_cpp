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
          ASSERT_EQ(i, (*it).first);
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

    TEST(constructors, move_constructor) {
        s21::set<double> origin{1, 2, 3, 4, 5};
        s21::set<double> copy = std::move(origin);
        ASSERT_EQ(copy.size(), 5);
        int i = 1;
        for (auto it_copy = copy.begin(); it_copy != copy.end(); ++it_copy) {
          ASSERT_EQ((*it_copy).first, i);
          i++;
        }
    }
}

namespace insert_suite {
    TEST(insert, empty_constructor) {
      s21::set<double> set;
      std::pair<s21::set<double>::iterator, bool> pair(set.insert(10));
      ASSERT_EQ(set.size(), 1);
      double first = (*pair.first).first;
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
      
      auto pair(set.insert(15));
      double first = (*pair.first).first;
      auto begin = set.begin();
      ASSERT_EQ((*begin).first, 1);
      ASSERT_EQ(first, 15);
      ASSERT_EQ(pair.second, false);
      ASSERT_EQ(set.size(), 5);

      auto number = set.find(16);
      ASSERT_EQ(number.itr, number.end);
      number = set.find(15);
      ASSERT_EQ((*number).first, 15);
      number = set.find(14);
      ASSERT_EQ(number.itr, number.end);

      ASSERT_FALSE(set.contains(21));
      ASSERT_FALSE(set.contains(19));
      ASSERT_TRUE(set.contains(15));
      ASSERT_TRUE(set.contains(1));

      auto it = set.find(15);
      set.erase(it);
      ASSERT_FALSE(set.contains(15));
      ASSERT_EQ(set.size(), 4);
    }

    TEST(insert, strings) {
      s21::set<std::string> set;
      // std::pair<s21::set<double>::iterator, bool> pair(set.insert(10));
      std::string words [] = {"", "aboba", "b", "ba", "boba", "oba"};
      set.insert("aboba");
      set.insert("aboba");
      ASSERT_EQ(set.size(), 1);
      set.insert("boba");
      set.insert("oba");
      set.insert("ba");
      set.insert("b");
      set.insert("");
      ASSERT_EQ(set.size(), 6);
      int i = 0;
      for (auto it = set.begin(); it != set.end(); ++it) {
        ASSERT_EQ((*it).first, words[i]);
        i++;
      }
      // auto it_const = set.cbegin();
      // ++it_const;
      // cout << *it_const << endl;
    }
}

namespace erase_suite {
    TEST (erase, empty_constructor) {
      s21::set<double> set;
      auto it = set.begin();
      auto end = set.end();
      set.erase(it);
      ++it;
      ASSERT_EQ(*it, *end);
    }

    TEST (erase, erase_using_iterator) {
      s21::set<double> set;
      set.insert(10);
      set.insert(15);
      set.insert(20);
      set.insert(18);
      set.insert(8);
      set.insert(1);

      auto it = set.begin();
      set.erase(it);
      ASSERT_EQ(set.size(), 5);
    }
}

namespace modifiers_suite {
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


namespace operators_suite {
    TEST(operators, equal) {
        s21::set<double> set1, set2;
        set1.insert(5);
        set2.insert(6);
        set2.insert(7);
        set1 = set2;
        ASSERT_EQ(set1.size(), 2);
        ASSERT_EQ(set2.size(), 2);
        ASSERT_FALSE(set1.contains(5));
        ASSERT_TRUE(set1.contains(7));
        ASSERT_TRUE(set2.contains(6));
    }

    TEST(operators, move) {
        s21::set<double> set1, set2;
        set1.insert(5);
        set2.insert(6);
        set2.insert(7);
        set1 = std::move(set2);
        ASSERT_EQ(set1.size(), 2);
        ASSERT_EQ(set2.size(), 0);
        ASSERT_FALSE(set1.contains(5));
        ASSERT_TRUE(set1.contains(7));
        ASSERT_FALSE(set2.contains(6));
        auto it = set2.begin();
        EXPECT_THROW(*it, std::out_of_range);
    }
}

namespace iterator_suite {
    TEST(iterators, iterator_add) {
        s21::set<double> set1;
        double numbers [] = {5, 6, 7};
        set1.insert(6);
        set1.insert(5);
        set1.insert(7);
        int i = 0;
        for (auto it = set1.begin(); it != set1.end(); ++it) {
            ASSERT_EQ((*it).first, numbers[i]);
            i++;
        }
    }

    TEST(iterators, iterator_sub) {
        s21::set<double> set1;
        double numbers [] = {5, 6, 7};
        int numbers_size = 3;
        set1.insert(6);
        set1.insert(5);
        set1.insert(7);
        int i = 2;
        auto it = set1.end();
        --it;
        for (; it != set1.end(); --it) {
            ASSERT_EQ((*it).first, numbers[i]);
            i--;
        }
    }

    TEST(iterators, const_iterator) {
        s21::set<double> set1;
        double numbers [] = {5, 6, 7};
        set1.insert(6);
        set1.insert(5);
        set1.insert(7);
        int i = 0;
        for (auto it = set1.cbegin(); it != set1.cend(); ++it) {
            ASSERT_EQ((*it).first, numbers[i]);
            i++;
        }
    }
}

namespace emplace_suite {
    TEST(emplace, insert_using_emplace) {
        s21::set<double> set1;
        double numbers [] = {5, 6, 7};
        set1.emplace(6);
        set1.emplace(5);
        set1.emplace(7);
        int i = 0;
        for (auto it = set1.begin(); it != set1.end(); ++it) {
            ASSERT_EQ((*it).first, numbers[i]);
            i++;
        }
    }
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
