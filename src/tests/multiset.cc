#include <gtest/gtest.h>

#include "s21_containersplus.h"

namespace multiset_constructors_suite {
    TEST(constructors, empty_constructor) {
        s21::multiset<double> multi;
        ASSERT_EQ(multi.size(), 0);
    }

    TEST(constructors, initializer_list) {
        s21::multiset<double> multiset{1, 2, 3, 4, 5, 4, 5};
        ASSERT_EQ(multiset.size(), 7);
        double numbers[] = {1, 2, 3, 4, 4, 5, 5};
        auto it = multiset.begin();
        for (int i = 0; i < 7; i++) {
          ASSERT_EQ(numbers[i], (*it).first);
          ++it;
        }
    }

    TEST(constructors, copy_constructor) {
        s21::multiset<double> origin{1, 2, 3, 4, 4};
        s21::multiset<double> copy(origin);
        ASSERT_EQ(copy.size(), origin.size());
        auto it_origin = origin.begin();
        for (auto it_copy = copy.begin(); it_copy != copy.end(); ++it_copy) {
          ASSERT_EQ(*it_origin, *it_copy);
          ++it_origin;
        }
    }

    TEST(constructors, move_constructor) {
        s21::multiset<double> origin{1, 2, 3, 4, 5, 4, 5};
        double numbers[] = {1, 2, 3, 4, 4, 5, 5};
        s21::multiset<double> copy = std::move(origin);
        ASSERT_EQ(copy.size(), 7);
        int i = 0;
        for (auto it_copy = copy.begin(); it_copy != copy.end(); ++it_copy) {
          ASSERT_EQ((*it_copy).first, numbers[i]);
          i++;
        }
    }
}  // namespace multiset_constructors_suite

namespace multiset_insert_suite {
    TEST(insert, empty_constructor) {
      s21::multiset<double> multiset;
      auto it = multiset.insert(10);
      ASSERT_EQ(multiset.size(), 1);
      ASSERT_EQ((*it).first, 10);
    }

    TEST(insert, insert_several_nodes) {
      s21::multiset<double> multiset;
      multiset.insert(1);
      multiset.insert(10);
      multiset.insert(12);
      multiset.insert(15);
      multiset.insert(20);
      multiset.insert(0);
      multiset.insert(20);
      multiset.insert(15);

      auto it_last_15 = multiset.insert(15);
      auto it = multiset.begin();
      ASSERT_EQ((*it).first, 0);
      ASSERT_EQ((*it_last_15).first, 15);
      ASSERT_EQ(multiset.size(), 9);

      auto it_first_15 = multiset.find(15);
      ASSERT_FALSE(it_last_15 == it_first_15);
      ++it_first_15;
      ++it_first_15;
      ASSERT_TRUE(it_last_15 == it_first_15);
      it = multiset.find(16);
      ASSERT_TRUE(it == multiset.end());

      // ASSERT_FALSE(multiset.contains(21));
      // ASSERT_FALSE(multiset.contains(19));
      // ASSERT_TRUE(multiset.contains(15));
      // ASSERT_TRUE(multiset.contains(1));

      // it = multiset.find(15);
      // multiset.erase(it);
      // ASSERT_TRUE(multiset.contains(15));
      // ASSERT_EQ(multiset.size(), 8);
    }

    TEST(insert, strings) {
      s21::multiset<std::string> multiset;
      // std::pair<s21::set<double>::iterator, bool> pair(set.insert(10));
      std::string words[] = {"", "aboba", "aboba", "b", "ba", "boba", "oba"};
      multiset.insert("aboba");
      multiset.insert("aboba");
      ASSERT_EQ(multiset.size(), 2);
      multiset.insert("boba");
      multiset.insert("oba");
      multiset.insert("ba");
      multiset.insert("b");
      multiset.insert("");
      ASSERT_EQ(multiset.size(), 7);
      int i = 0;
      for (auto it = multiset.begin(); it != multiset.end(); ++it) {
        ASSERT_EQ((*it).first, words[i]);
        i++;
      }
      // auto it_const = set.cbegin();
      // ++it_const;
      // cout << *it_const << endl;
    }
}  // namespace multiset_insert_suite

namespace multiset_erase_suite {
    TEST(erase, empty_constructor) {
      s21::multiset<double> multiset;
      auto it = multiset.begin();
      auto end = multiset.end();
      multiset.erase(it);
      ++it;
      ASSERT_EQ(*it, *end);
    }

    TEST(erase, erase_using_iterator) {
      s21::multiset<double> multiset;
      multiset.insert(10);
      multiset.insert(15);
      multiset.insert(20);
      multiset.insert(18);
      multiset.insert(8);
      multiset.insert(1);
      multiset.insert(10);


      auto it = multiset.begin();
      multiset.erase(it);
      ASSERT_EQ(multiset.size(), 6);
      double numbers_1[] = {8, 10, 10, 15, 18, 20};
      int i = 0;
      for (it = multiset.begin(); it != multiset.end(); ++it) {
        ASSERT_EQ((*it).first, numbers_1[i]);
        i++;
      }

      it = multiset.find(10);
      multiset.erase(it);
      ASSERT_EQ(multiset.size(), 5);
      double numbers_2[] = {8, 10, 15, 18, 20};
      i = 0;
      for (it = multiset.begin(); it != multiset.end(); ++it) {
        ASSERT_EQ((*it).first, numbers_2[i]);
        i++;
      }
    }
}  // namespace multiset_erase_suite

namespace multiset_modifiers_suite {
    TEST(modifiers, swap) {
        s21::multiset<double> multiset1, multiset2;
        multiset1.insert(5);
        multiset1.insert(5);
        multiset1.insert(5);
        multiset2.insert(6);
        multiset2.insert(7);
        multiset1.swap(multiset2);
        ASSERT_EQ(multiset1.size(), 2);
        ASSERT_EQ(multiset2.size(), 3);
        ASSERT_TRUE(multiset1.contains(6));
        ASSERT_TRUE(multiset1.contains(7));
        ASSERT_TRUE(multiset2.contains(5));
    }

    TEST(modifiers, merge) {
        s21::multiset<double> multiset1, multiset2;
        multiset1.insert(5);
        multiset1.insert(5);
        multiset1.insert(5);
        multiset2.insert(6);
        multiset2.insert(7);
        multiset1.merge(multiset2);
        ASSERT_EQ(multiset1.size(), 5);
        ASSERT_EQ(multiset2.size(), 2);
        ASSERT_TRUE(multiset1.contains(6));
        ASSERT_TRUE(multiset1.contains(7));
        ASSERT_TRUE(multiset2.contains(6));
    }
}  // namespace multiset_modifiers_suite

namespace multiset_operators_suite {
    TEST(operators, equal) {
        s21::multiset<double> multiset1, multiset2;
        multiset1.insert(5);
        multiset1.insert(5);
        multiset1.insert(5);
        multiset2.insert(6);
        multiset2.insert(7);
        multiset1 = multiset2;
        ASSERT_EQ(multiset1.size(), 2);
        ASSERT_EQ(multiset2.size(), 2);
        ASSERT_FALSE(multiset1.contains(5));
        ASSERT_TRUE(multiset1.contains(7));
        ASSERT_TRUE(multiset2.contains(6));
    }

    TEST(operators, move) {
        s21::multiset<double> multiset1, multiset2;
        multiset1.insert(5);
        multiset1.insert(5);
        multiset1.insert(5);
        multiset2.insert(6);
        multiset2.insert(7);
        multiset1 = std::move(multiset2);
        ASSERT_EQ(multiset1.size(), 2);
        ASSERT_EQ(multiset2.size(), 0);
        ASSERT_FALSE(multiset1.contains(5));
        ASSERT_TRUE(multiset1.contains(7));
        ASSERT_FALSE(multiset2.contains(6));
        auto it = multiset2.begin();
        EXPECT_THROW(*it, std::out_of_range);
    }
}  // namespace multiset_operators_suite

namespace multiset_iterator_suite {
    TEST(iterators, iterator_add) {
        s21::multiset<double> multiset;
        double numbers[] = {5, 5, 6, 6, 7};
        multiset.insert(6);
        multiset.insert(5);
        multiset.insert(7);
        multiset.insert(6);
        multiset.insert(5);
        int i = 0;
        for (auto it = multiset.begin(); it != multiset.end(); ++it) {
            ASSERT_EQ((*it).first, numbers[i]);
            i++;
        }
    }

    TEST(iterators, iterator_sub) {
        s21::multiset<double> multiset;
        double numbers[] = {5, 5, 5, 6, 7};
        multiset.insert(5);
        multiset.insert(6);
        multiset.insert(5);
        multiset.insert(7);
        multiset.insert(5);
        int i = 4;
        auto it = multiset.end();
        --it;
        for (; it != multiset.end(); --it) {
            ASSERT_EQ((*it).first, numbers[i]);
            i--;
        }
    }

    TEST(iterators, const_iterator) {
        s21::multiset<double> multiset;
        double numbers[] = {2, 2, 5, 6, 7};
        multiset.insert(6);
        multiset.insert(5);
        multiset.insert(7);
        multiset.insert(2);
        multiset.insert(2);
        int i = 0;
        for (auto it = multiset.cbegin(); it != multiset.cend(); ++it) {
            ASSERT_EQ((*it).first, numbers[i]);
            i++;
        }
    }
}  // namespace multiset_iterator_suite

namespace multiset_additional_functions_suite {
    TEST(additional_functions, lower_bound) {
        s21::multiset<double> multiset{5, 6, 7, 7, 8};
        double numbers[] = {7, 7, 8};
        auto it = multiset.lower_bound(7);

        int i = 0;
        for (; it != multiset.end(); ++it) {
            ASSERT_EQ((*it).first, numbers[i]);
            i++;
        }
    }

    TEST(additional_functions, upper_bound) {
        s21::multiset<double> multiset{5, 6, 7, 7, 8};
        double numbers[] = {8};
        auto it = multiset.upper_bound(7);

        int i = 0;
        for (; it != multiset.end(); ++it) {
            ASSERT_EQ((*it).first, numbers[i]);
            i++;
        }
    }

    TEST(additional_functions, equal_range) {
      s21::multiset<double> multiset{5, 6, 7, 7, 8};
      double numbers[] = {7, 7, 8};
      auto it = multiset.equal_range(7);

      int i = 0;
      for (; it.first != it.second; ++it.first) {
        ASSERT_EQ((*it.first).first, numbers[i]);
        i++;
      }
    }
}  // namespace multiset_additional_functions_suite

namespace multiset_emplace_suite {
    TEST(emplace, insert_using_emplace) {
        s21::multiset<double> multiset;
        double numbers[] = {5, 6, 7, 7, 8};
        multiset.emplace(8);
        multiset.emplace(6);
        multiset.emplace(7);
        multiset.emplace(5);
        multiset.emplace(7);
        int i = 0;
        for (auto it = multiset.begin(); it != multiset.end(); ++it) {
            ASSERT_EQ((*it).first, numbers[i]);
            i++;
        }
    }
}  // namespace multiset_emplace_suite
