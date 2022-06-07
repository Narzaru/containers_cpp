#include <gtest/gtest.h>

#include "s21_containersplus.h"

namespace multiset_constructors_suite {
    TEST(constructors, empty_constructor) {
        s21::multiset<double> multi;
        std::multiset<double> multi_origin;
        ASSERT_EQ(multi.size(), 0);
        ASSERT_EQ(multi_origin.size(), 0);
        ASSERT_EQ(multi_origin.max_size(), multi.max_size());
        ASSERT_EQ(multi.empty(), multi_origin.empty());
    }

    TEST(constructors, initializer_list) {
        s21::multiset<double> multiset{1, 2, 3, 4, 5, 4, 5};
        std::multiset<double> origin{1, 2, 3, 4, 5, 4, 5};
        ASSERT_EQ(multiset.size(), origin.size());
        auto it_origin = origin.begin();
        for (auto it = multiset.begin(); it != multiset.end(); ++it) {
          ASSERT_EQ((*it).first, *it_origin);
          ++it_origin;
        }
        multiset.clear();
        origin.clear();
        ASSERT_EQ(multiset.size(), origin.size());
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
        std::multiset<double> multiset_origin{1, 2, 3, 4, 4, 5, 5};
        s21::multiset<double> copy = std::move(origin);
        ASSERT_EQ(copy.size(), 7);
        auto it_origin = multiset_origin.begin();
        for (auto it_copy = copy.begin(); it_copy != copy.end(); ++it_copy) {
          ASSERT_EQ((*it_copy).first, *it_origin);
          ++it_origin;
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
      std::multiset<double> origin{1, 10, 12, 15, 20, 0, 20, 15};
      multiset.insert(1);
      multiset.insert(10);
      multiset.insert(12);
      multiset.insert(15);
      multiset.insert(20);
      multiset.insert(0);
      multiset.insert(20);
      multiset.insert(15);

      auto it_last_15 = multiset.insert(15);
      auto it_last_15_origin = origin.insert(15);
      auto it = multiset.begin();
      auto it_origin = origin.begin();
      ASSERT_EQ((*it).first, *it_origin);
      ASSERT_EQ((*it_last_15).first, *it_last_15_origin);
      ASSERT_EQ(multiset.size(), origin.size());

      auto it_first_15 = multiset.find(15);
      auto it_first_15_origin = origin.find(15);
      ASSERT_EQ(it_last_15 == it_first_15,
                it_last_15_origin == it_first_15_origin);
      ASSERT_FALSE(it_last_15 == it_first_15);
      ++it_first_15;
      ++it_first_15;
      ++it_first_15_origin;
      ++it_first_15_origin;
      ASSERT_EQ(it_last_15 == it_first_15,
                it_last_15_origin == it_first_15_origin);
      ASSERT_TRUE(it_last_15 == it_first_15);

      it = multiset.find(16);

      ASSERT_TRUE(it == multiset.end());
    }

    TEST(insert, strings) {
      s21::multiset<std::string> multiset;
      std::multiset<std::string> origin{"", "aboba", "aboba", "b", "ba", "boba", "oba"};
      multiset.insert("aboba");
      multiset.insert("aboba");
      ASSERT_EQ(multiset.size(), 2);
      multiset.insert("boba");
      multiset.insert("oba");
      multiset.insert("ba");
      multiset.insert("b");
      multiset.insert("");
      ASSERT_EQ(multiset.size(), origin.size());
      auto it_origin = origin.begin();
      for (auto it = multiset.begin(); it != multiset.end() && it_origin != origin.end(); ++it, ++it_origin) {
        ASSERT_EQ((*it).first, *it_origin);
      }
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
      ASSERT_EQ(multiset.size(), 0);
    }

    TEST(erase, erase_using_iterator) {
      s21::multiset<double> multiset;
      std::multiset<double> origin{8, 10, 10, 15, 18, 20};
      multiset.insert(10);
      multiset.insert(15);
      multiset.insert(20);
      multiset.insert(18);
      multiset.insert(8);
      multiset.insert(1);
      multiset.insert(10);

      auto it = multiset.begin();
      auto it_origin = origin.begin();
      multiset.erase(it);
      ASSERT_EQ(multiset.size(), origin.size());
      for (it = multiset.begin(); it != multiset.end() && it_origin != origin.end(); ++it, ++it_origin) {
        ASSERT_EQ((*it).first, *it_origin);
      }

      it = multiset.find(10);
      multiset.erase(it);
      origin.erase(origin.find(10));
      ASSERT_EQ(multiset.size(), origin.size());
      for (it = multiset.begin(), it_origin = origin.begin();
      it != multiset.end() && it_origin != origin.end(); ++it, ++it_origin) {
        ASSERT_EQ((*it).first, *it_origin);
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
        std::multiset<double> origin1{5, 5, 5}, origin2{6, 7};
        multiset1.insert(5);
        multiset1.insert(5);
        multiset1.insert(5);
        multiset2.insert(6);
        multiset2.insert(7);
        multiset1.merge(multiset2);
        origin1.merge(origin2);
        ASSERT_EQ(multiset1.size(), origin1.size());
        ASSERT_EQ(multiset2.size(), origin2.size());
        ASSERT_TRUE(multiset1.contains(6));
        ASSERT_TRUE(multiset1.contains(7));
        ASSERT_FALSE(multiset2.contains(6));
    }
}  // namespace multiset_modifiers_suite

namespace multiset_operators_suite {
    TEST(operators, equal) {
        s21::multiset<double> multiset1, multiset2;
        std::multiset<double> origin1{5, 5, 5}, origin2{6, 7};
        multiset1.insert(5);
        multiset1.insert(5);
        multiset1.insert(5);
        multiset2.insert(6);
        multiset2.insert(7);
        multiset1 = multiset2;
        origin1 = origin2;
        ASSERT_EQ(multiset1.size(), origin1.size());
        ASSERT_EQ(multiset2.size(), origin2.size());
        ASSERT_EQ(multiset1.find(5) == multiset1.end(), origin1.find(5) == origin1.end());
        ASSERT_EQ(multiset1.find(7) != multiset1.end(), origin1.find(7) != origin1.end());
        ASSERT_EQ(multiset2.find(6) != multiset2.end(), origin2.find(6) != origin2.end());
    }

    TEST(operators, move) {
        s21::multiset<double> multiset1{5, 5, 5}, multiset2{6, 7};
        std::multiset<double> origin1{5, 5, 5}, origin2{6, 7};
        multiset1 = std::move(multiset2);
        origin1 = std::move(origin2);
        ASSERT_EQ(multiset1.size(), origin1.size());
        ASSERT_EQ(multiset2.size(), origin2.size());
        ASSERT_FALSE(multiset1.contains(5));
        ASSERT_TRUE(multiset1.contains(7));
        ASSERT_FALSE(multiset2.contains(6));
        auto it = multiset2.begin();
        EXPECT_THROW(*it, std::out_of_range);
    }
}  // namespace multiset_operators_suite

namespace multiset_iterator_suite {
    TEST(iterators, iterator_add) {
        s21::multiset<double> multiset{6, 5, 7, 6, 5};
        std::multiset<double> origin{5, 5, 6, 6, 7};
        auto it_origin = origin.begin();
        for (auto it = multiset.begin();
        it != multiset.end() && it_origin != origin.end(); ++it, ++it_origin) {
            ASSERT_EQ((*it).first, *it_origin);
        }
    }

    TEST(iterators, iterator_sub) {
        s21::multiset<double> multiset{5, 6, 5, 7, 5};
        std::multiset<double> origin{5, 5, 5, 6, 7};

        auto it_origin = origin.end();
        auto it = multiset.end();
        --it;
        --it_origin;
        for (; it != multiset.end() && it_origin != origin.end(); --it, --it_origin) {
            ASSERT_EQ((*it).first, *it_origin);
        }
    }

    TEST(iterators, const_iterator) {
        s21::multiset<double> multiset{6, 5, 7, 2, 2};
        std::multiset<double> origin{2, 2, 5, 6, 7};
        auto it_origin = origin.cbegin();
        for (auto it = multiset.cbegin();
        it != multiset.cend() && it_origin != origin.cend(); ++it, ++it_origin) {
            ASSERT_EQ((*it).first, *it_origin);
        }
    }
}  // namespace multiset_iterator_suite

namespace multiset_additional_functions_suite {
    TEST(additional_functions, lower_bound) {
        s21::multiset<double> multiset{5, 6, 7, 7, 8};
        std::multiset<double> origin{5, 6, 7, 7, 8};
        auto it = multiset.lower_bound(7);
        auto it_origin = origin.lower_bound(7);
        for (; it != multiset.end() && it_origin != origin.end(); ++it, ++it_origin) {
            ASSERT_EQ((*it).first, *it_origin);
        }
    }

    TEST(additional_functions, upper_bound) {
        s21::multiset<double> multiset{5, 6, 7, 7, 8};
        std::multiset<double> origin{5, 6, 7, 7, 8};
        auto it = multiset.upper_bound(7);
        auto it_origin = origin.upper_bound(7);
        for (; it != multiset.end(); ++it, ++it_origin) {
            ASSERT_EQ((*it).first, *it_origin);
        }
    }

    TEST(additional_functions, equal_range) {
      s21::multiset<double> multiset{5, 6, 7, 7, 8};
      std::multiset<double> origin{5, 6, 7, 7, 8};
      auto it = multiset.equal_range(7);
      auto it_origin = origin.equal_range(7);

      for (; it.first != it.second && it_origin.first != it_origin.second; ++it.first, ++it_origin.first) {
        ASSERT_EQ((*it.first).first, *it_origin.first);
      }
    }
}  // namespace multiset_additional_functions_suite

namespace multiset_emplace_suite {
    TEST(emplace, insert_using_emplace) {
        s21::multiset<double> multiset;
        std::multiset<double> origin;
        multiset.emplace(8);
        multiset.emplace(6);
        multiset.emplace(7);
        multiset.emplace(5);
        multiset.emplace(7);
        origin.emplace(8);
        origin.emplace(6);
        origin.emplace(7);
        origin.emplace(5);
        origin.emplace(7);
        auto it_origin = origin.begin();
        for (auto it = multiset.begin();
        it != multiset.end() && it_origin != origin.end(); ++it, ++it_origin) {
            ASSERT_EQ((*it).first, *it_origin);
        }
    }
}  // namespace multiset_emplace_suite
