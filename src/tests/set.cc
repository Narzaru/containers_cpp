#include <gtest/gtest.h>

#include "s21_containers.h"

namespace set_constructors_suite {
    TEST(constructors, empty_set_constructor) {
        s21::set<double> set;
        ASSERT_EQ(set.size(), 0);
    }

    TEST(constructors, set_initializer_list) {
        s21::set<double> set{1, 2, 3, 4, 5};
        ASSERT_EQ(set.size(), 5);
        auto it = set.begin();
        for (int i = 1; i <= 5; i++) {
          ASSERT_EQ(i, (*it).first);
          ++it;
        }
    }

    TEST(constructors, copy_set_constructor) {
        s21::set<double> origin{1, 2, 3, 4, 5};
        s21::set<double> copy(origin);
        ASSERT_EQ(copy.size(), origin.size());
        auto it_origin = origin.begin();
        for (auto it_copy = copy.begin(); it_copy != copy.end(); ++it_copy) {
          ASSERT_EQ(*it_origin, *it_copy);
          ++it_origin;
        }
    }

    TEST(constructors, move_set_constructor) {
        s21::set<double> origin{1, 2, 3, 4, 5};
        s21::set<double> copy = std::move(origin);
        ASSERT_EQ(copy.size(), 5);
        int i = 1;
        for (auto it_copy = copy.begin(); it_copy != copy.end(); ++it_copy) {
          ASSERT_EQ((*it_copy).first, i);
          i++;
        }
    }
}  // namespace set_constructors_suite

namespace set_insert_suite {
    TEST(insert, empty_set_constructor) {
      s21::set<double> set;
      std::pair<s21::set<double>::iterator, bool> pair(set.insert(10));
      ASSERT_EQ(set.size(), 1);
      double first = (*pair.first).first;
      ASSERT_EQ(first, 10);
      ASSERT_EQ(pair.second, true);
    }

    TEST(insert, set_several_nodes) {
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
      std::string words[] = {"", "aboba", "b", "ba", "boba", "oba"};
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
}  // namespace set_insert_suite

namespace set_erase_suite {
    TEST(erase, empty_constructor) {
      s21::set<double> set;
      auto it = set.begin();
      auto end = set.end();
      set.erase(it);
      ++it;
      ASSERT_EQ(*it, *end);
    }

    TEST(erase, erase_using_iterator) {
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

    TEST(erase, erase_with_fix_up) {
      s21::set<double> set{10, 15, 20, 18, 8, 1, 12, 25};
      double numbers_before[] = {1, 8, 10, 12, 15, 18, 20, 25};
      int i = 0;
      for (auto iter = set.begin(); iter != set.end(); ++iter) {
          ASSERT_EQ((*iter).first, numbers_before[i]);
          i++;
      }

      auto it = set.find(1);
      set.erase(it);
      ASSERT_EQ(set.size(), 7);
      double numbers_after[] = {8, 10, 12, 15, 18, 20, 25};
      i = 0;
      for (it = set.begin(); it != set.end(); ++it) {
          ASSERT_EQ((*it).first, numbers_after[i]);
          i++;
      }
      set.insert(1);

      it = set.find(8);
      set.erase(it);
      ASSERT_EQ(set.size(), 7);
      double numbers_after_1[] = {1, 10, 12, 15, 18, 20, 25};
      i = 0;
      for (it = set.begin(); it != set.end(); ++it) {
          ASSERT_EQ((*it).first, numbers_after_1[i]);
          i++;
      }

      set.insert(8);
      set.erase(set.find(18));
      double numbers_after_2[] = {1, 8, 10, 12, 15, 20, 25};
      i = 0;
      for (it = set.begin(); it != set.end(); ++it) {
          ASSERT_EQ((*it).first, numbers_after_2[i]);
          i++;
      }
      set.insert(18);
      set.insert(7);
      set.insert(4);
      set.insert(2);
      set.insert(0);
      set.insert(16);
      set.erase(set.find(1));
      double numbers_after_3[] = {0, 2, 4, 7, 8, 10, 12, 15, 16, 18, 20, 25};
      i = 0;
      for (it = set.begin(); it != set.end(); ++it) {
          ASSERT_EQ((*it).first, numbers_after_3[i]);
          i++;
      }
      set.insert(1);

      set.erase(set.find(1));
      double numbers_after_4[] = {0, 2, 4, 7, 8, 10, 12, 15, 16, 18, 20, 25};
      i = 0;
      for (it = set.begin(); it != set.end(); ++it) {
          ASSERT_EQ((*it).first, numbers_after_4[i]);
          i++;
      }
      set.insert(1);

      set.erase(set.find(2));
      double numbers_after_5[] = {0, 1, 4, 7, 8, 10, 12, 15, 16, 18, 20, 25};
      i = 0;
      for (it = set.begin(); it != set.end(); ++it) {
          ASSERT_EQ((*it).first, numbers_after_5[i]);
          i++;
      }

      s21::set<double> set_new{1, 0, 3, 2, 7, 4, 8, 12,
          10, 15, 16, 18, 20, 25, 5, 6, 9, 11, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35};
      double numbers_after_6[] = {1, 2, 5, 6, 7, 8, 9, 10, 11, 21, 22, 23, 24, 25, 30, 31, 32, 33, 34, 35};
      set_new.erase(set_new.find(18));
      set_new.erase(set_new.find(15));
      set_new.erase(set_new.find(0));
      set_new.erase(set_new.find(3));
      set_new.erase(set_new.find(4));
      set_new.erase(set_new.find(20));
      set_new.erase(set_new.find(16));
      set_new.erase(set_new.find(12));
      i = 0;
      for (it = set_new.begin(); it != set_new.end(); ++it) {
        ASSERT_EQ((*it).first, numbers_after_6[i]);
        i++;
      }
    }
}  // namespace set_erase_suite

namespace set_modifiers_suite {
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
}  // namespace set_modifiers_suite

namespace set_operators_suite {
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
}  // namespace set_operators_suite

namespace set_iterator_suite {
    TEST(iterators, iterator_add) {
        s21::set<double> set1;
        double numbers[] = {5, 6, 7};
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
        double numbers[] = {5, 6, 7};
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
        double numbers[] = {5, 6, 7};
        set1.insert(6);
        set1.insert(5);
        set1.insert(7);
        int i = 0;
        for (auto it = set1.cbegin(); it != set1.cend(); ++it) {
            ASSERT_EQ((*it).first, numbers[i]);
            i++;
        }
    }
}  // namespace set_iterator_suite

namespace set_emplace_suite {
    TEST(emplace, insert_using_emplace) {
        s21::set<double> set1;
        double numbers[] = {5, 6, 7};
        set1.emplace(6);
        set1.emplace(5);
        set1.emplace(7);
        int i = 0;
        for (auto it = set1.begin(); it != set1.end(); ++it) {
            ASSERT_EQ((*it).first, numbers[i]);
            i++;
        }
    }
}  // namespace set_emplace_suite
