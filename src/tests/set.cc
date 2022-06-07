#include <gtest/gtest.h>

#include "s21_containers.h"

namespace set_constructors_suite {
    TEST(constructors, empty_set_constructor) {
        s21::set<double> set;
        std::set<double> origin;
        ASSERT_EQ(set.size(), origin.size());
        ASSERT_EQ(set.size(), 0);
        ASSERT_EQ(set.max_size(), origin.max_size());
    }

    TEST(constructors, set_initializer_list) {
        s21::set<double> set{1, 2, 3, 4, 5};
        std::set<double> origin{1, 2, 3, 4, 5};
        ASSERT_EQ(set.size(), 5);
        ASSERT_EQ(set.size(), origin.size());
        auto it = set.begin();
        auto it_origin = origin.begin();
        for (; it != set.end() && it_origin != origin.end();
             ++it, ++it_origin) {
          ASSERT_EQ((*it).first, *it_origin);
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
        std::set<double> std_origin{1, 2, 3, 4, 5};
        ASSERT_EQ(copy.size(), 5);
        auto it = copy.begin();
        auto it_origin = std_origin.begin();
        for (; it != copy.end() && it_origin != std_origin.end();
             ++it, ++it_origin) {
          ASSERT_EQ((*it).first, *it_origin);
        }
    }
}  // namespace set_constructors_suite

namespace set_insert_suite {
    TEST(insert, empty_set_constructor) {
      s21::set<double> set;
      std::set<double> origin;
      auto it = set.insert(10);
      auto it_origin = origin.insert(10);
      ASSERT_EQ(set.size(), 1);
      ASSERT_EQ(set.size(), origin.size());
      ASSERT_EQ((*it.first).first, *it_origin.first);
      ASSERT_EQ(it.second, it_origin.second);
    }

    TEST(insert, set_several_nodes) {
      s21::set<double> set;
      std::set<double> origin{1, 10, 12, 15, 20};
      set.insert(1);
      set.insert(10);
      set.insert(12);
      set.insert(15);
      set.insert(20);

      auto pair_set(set.insert(15));
      auto pair_origin(origin.insert(15));
      double first = (*pair_set.first).first;
      auto begin = set.begin();
      ASSERT_EQ((*begin).first, 1);
      ASSERT_EQ(first, *pair_origin.first);
      ASSERT_EQ(pair_set.second, pair_origin.second);
      ASSERT_EQ(set.size(), 5);
      ASSERT_EQ(set.size(), origin.size());

      auto number = set.find(16);
      ASSERT_TRUE(number == set.end());
      number = set.find(15);
      ASSERT_EQ((*number).first, 15);

      ASSERT_FALSE(set.contains(21));
      ASSERT_FALSE(set.contains(19));
      ASSERT_TRUE(set.contains(15));
      ASSERT_TRUE(set.contains(1));
    }

    TEST(insert, strings) {
      s21::set<std::string> set;
      std::set<std::string> origin{"", "aboba", "b", "ba", "boba", "oba"};
      set.insert("aboba");
      set.insert("aboba");
      ASSERT_EQ(set.size(), 1);
      set.insert("boba");
      set.insert("oba");
      set.insert("ba");
      set.insert("b");
      set.insert("");
      ASSERT_EQ(set.size(), 6);
      ASSERT_EQ(set.size(), origin.size());
      auto it = set.begin();
      auto it_origin = origin.begin();
      for (; it != set.end() && it_origin != origin.end();
           ++it, ++it_origin) {
        ASSERT_EQ((*it).first, *it_origin);
      }
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
      std::set<double> origin{10, 15, 20, 18, 8, 1};
      set.insert(10);
      set.insert(15);
      set.insert(20);
      set.insert(18);
      set.insert(8);
      set.insert(1);

      auto it = set.begin();
      auto it_origin = origin.begin();
      set.erase(it);
      origin.erase(it_origin);
      ASSERT_EQ(set.size(), 5);
      ASSERT_EQ(set.size(), origin.size());
      it = set.begin();
      it_origin = origin.begin();
      for (; it != set.end() && it_origin != origin.end(); ++it, ++it_origin) {
        ASSERT_EQ((*it).first, *it_origin);
      }
    }

    TEST(erase, erase_with_fix_up) {
      s21::set<double> set{10, 15, 20, 18, 8, 1, 12, 25};
      std::set<double> origin{10, 15, 20, 18, 8, 1, 12, 25};
      auto it = set.begin();
      auto it_origin = origin.begin();
      for (; it != set.end() && it_origin != origin.end(); ++it, ++it_origin) {
        ASSERT_EQ((*it).first, *it_origin);
      }
      it = set.find(1);
      it_origin = origin.find(1);
      set.erase(it);
      origin.erase(it_origin);
      ASSERT_EQ(set.size(), 7);
      ASSERT_EQ(set.size(), origin.size());
      it = set.begin();
      it_origin = origin.begin();
      for (; it != set.end() && it_origin != origin.end(); ++it, ++it_origin) {
        ASSERT_EQ((*it).first, *it_origin);
      }
      set.insert(1);
      origin.insert(1);
      it = set.find(8);
      it_origin = origin.find(8);
      set.erase(it);
      origin.erase(it_origin);
      ASSERT_EQ(set.size(), origin.size());
      it = set.begin();
      it_origin = origin.begin();
      for (; it != set.end() && it_origin != origin.end(); ++it, ++it_origin) {
        ASSERT_EQ((*it).first, *it_origin);
      }
      set.insert(8);
      origin.insert(8);
      set.erase(set.find(18));
      origin.erase(origin.find(18));
      it = set.begin();
      it_origin = origin.begin();
      for (; it != set.end() && it_origin != origin.end(); ++it, ++it_origin) {
        ASSERT_EQ((*it).first, *it_origin);
      }
    }

    TEST(erase, additional_erase_test) {
      s21::set<double> set{1,  0,  3,  2,  7,  4,  8,  12, 10, 15,
                               16, 18, 20, 25, 5,  6,  9,  11, 21, 22,
                               23, 24, 30, 31, 32, 33, 34, 35};
      std::set<double> origin{1,  2,  5,  6,  7,  8,  9,  10, 11, 21,
                                  22, 23, 24, 25, 30, 31, 32, 33, 34, 35};
      set.erase(set.find(18));
      set.erase(set.find(15));
      set.erase(set.find(0));
      set.erase(set.find(3));
      set.erase(set.find(4));
      set.erase(set.find(20));
      set.erase(set.find(16));
      set.erase(set.find(12));
      auto it = set.begin();
      auto it_origin = origin.begin();
      for (; it != set.end() && it_origin != origin.end(); ++it, ++it_origin) {
        ASSERT_EQ((*it).first, *it_origin);
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
        s21::set<double> set1{5}, set2{6, 7};
        std::set<double> origin1{5}, origin2{6, 7};
        set1.merge(set2);
        origin1.merge(origin2);
        ASSERT_EQ(set1.size(), origin1.size());
        ASSERT_EQ(set2.size(), origin2.size());
        auto it = set1.begin();
        auto it_origin = origin1.begin();
        for (; it != set1.end() && it_origin != origin1.end();
             ++it, ++it_origin) {
          ASSERT_EQ((*it).first, *it_origin);
        }
    }
}  // namespace set_modifiers_suite

namespace set_operators_suite {
    TEST(operators, equal) {
        s21::set<double> set1{5}, set2{6, 7};
        std::set<double> origin1{5}, origin2{6, 7};

        set1 = set2;
        origin1 = origin2;
        ASSERT_EQ(set1.size(), set2.size());
        ASSERT_EQ(set1.size(), origin1.size());
        ASSERT_EQ(set2.size(), 2);
        auto it = set1.begin();
        auto it_origin = origin1.begin();
        for (; it != set1.end() && it_origin != origin1.end();
             ++it, ++it_origin) {
          ASSERT_EQ((*it).first, *it_origin);
        }
    }

    TEST(operators, move) {
        s21::set<double> set1{5}, set2{6, 7};
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
        s21::set<double> set{5, 6, 7};
        std::set<double> origin{5, 6, 7};
        auto it = set.begin();
        auto it_origin = origin.begin();
        for (; it != set.end() && it_origin != origin.end();
             ++it, ++it_origin) {
          ASSERT_EQ((*it).first, *it_origin);
        }
    }

    TEST(iterators, iterator_sub) {
      s21::set<double> set{5, 6, 7};
      std::set<double> origin{5, 6, 7};
      auto it = set.end();
      auto it_origin = origin.end();
      --it;
      --it_origin;
      for (; it != set.end() && it_origin != origin.end(); ++it, ++it_origin) {
        ASSERT_EQ((*it).first, *it_origin);
      }
    }

    TEST(iterators, const_iterator) {
      s21::set<double> set{5, 6, 7};
      std::set<double> origin{5, 6, 7};
      auto it = set.cbegin();
      auto it_origin = origin.cbegin();
      for (; it != set.cend() && it_origin != origin.cend(); ++it, ++it_origin) {
        ASSERT_EQ((*it).first, *it_origin);
      }
    }
}  // namespace set_iterator_suite

namespace set_emplace_suite {
    TEST(emplace, insert_using_emplace) {
        s21::set<double> set;
        std::set<double> origin;
        set.emplace(6);
        set.emplace(5);
        set.emplace(7);
        origin.emplace(6);
        origin.emplace(5);
        origin.emplace(7);
        auto it = set.begin();
        auto it_origin = origin.begin();
        for (; it != set.end() && it_origin != origin.end();
             ++it, ++it_origin) {
          ASSERT_EQ((*it).first, *it_origin);
        }
    }
}  // namespace set_emplace_suite
