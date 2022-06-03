#include <gtest/gtest.h>
#include "s21_map.h"
#include <iostream>

using namespace std;

namespace constructors_suite {
    TEST(constructors, empty_constructor) {
        s21::map<int, double> map;
        ASSERT_EQ(map.size(), 0);
    }

    TEST(constructors, initializer_list) {
        s21::map<int, double> map{{1, 1}, {2, 2}, {3, 3}};
        ASSERT_EQ(map.size(), 3);
        for (auto it = map.begin(); it != map.end(); ++it) {
          std::pair<int, double> pair = *it;
          cout << pair.first;
          cout << " : ";
          cout << pair.second << endl;
        }
    }
}

namespace insert_suite {
    TEST(insert, insert_several_pairs) {
        s21::map<int, std::string> map;
        map.insert(std::make_pair(1, "One_first"));
        map.insert(std::make_pair(2, "Two"));
        map.insert(std::make_pair(1, "One_second"));
        map.insert(std::make_pair(0, "Zero"));
        map.insert(std::make_pair(1, "One_third"));
        ASSERT_EQ(map.size(), 3);
        for (auto it = map.begin(); it != map.end(); ++it) {
          std::pair<int, std::string> pair = *it;
          cout << pair.first;
          cout << " : ";
          cout << pair.second << endl;
        }
        // auto it = tree.end();
        // for (; it != tree.begin(); --it) {
        //   cout << (*it).first << endl;
        // }
        // cout << (*it).first << endl;
    }

    TEST(insert, insert_several_keys_values) {
        s21::map<int, std::string> map;
        map.insert(1, "One_first");
        map.insert(2, "Two");
        map.insert(1, "One_second");
        map.insert(0, "Zero");
        map.insert(1, "One_third");
        ASSERT_EQ(map.size(), 3);
        for (auto it = map.begin(); it != map.end(); ++it) {
          std::pair<int, std::string> pair = *it;
          cout << pair.first;
          cout << " : ";
          cout << pair.second << endl;
        }
        // auto it = tree.end();
        // for (; it != tree.begin(); --it) {
        //   cout << (*it).first << endl;
        // }
        // cout << (*it).first << endl;
    }

    TEST(insert, insert_or_assign) {
        s21::map<int, std::string> map;
        map.insert_or_assign(1, "One_first");
        map.insert_or_assign(2, "Two");
        map.insert_or_assign(1, "One_second");
        map.insert_or_assign(0, "Zero");
        map.insert_or_assign(1, "One_third");
        ASSERT_EQ(map.size(), 3);
        for (auto it = map.begin(); it != map.end(); ++it) {
          std::pair<int, std::string> pair = *it;
          cout << pair.first;
          cout << " : ";
          cout << pair.second << endl;
        }
        // auto it = tree.end();
        // for (; it != tree.begin(); --it) {
        //   cout << (*it).first << endl;
        // }
        // cout << (*it).first << endl;
    }
}

namespace erase_suite {
    TEST(erase, erase_elements) {
        s21::map<int, std::string> map{{1, "One"}, {2, "Two"}, {3, "Three"}};
        ASSERT_EQ(map.size(), 3);
        auto it = map.begin();
        ++it;
        map.erase(it);
        ASSERT_EQ(map.size(), 2);
        EXPECT_THROW(map.at(2), std::out_of_range);

        it = map.begin();
        ASSERT_EQ((*it).first, 1);
        ASSERT_EQ((*it).second, "One");
        ++it;
        ASSERT_EQ((*it).first, 3);
        ASSERT_EQ((*it).second, "Three");
        ++it;
        ASSERT_TRUE(it == map.end());
    }

    TEST(constructors, initializer_list) {
        s21::map<int, double> map{{1, 1}, {2, 2}, {3, 3}};
        ASSERT_EQ(map.size(), 3);
        for (auto it = map.begin(); it != map.end(); ++it) {
          std::pair<int, double> pair = *it;
          cout << pair.first;
          cout << " : ";
          cout << pair.second << endl;
        }
    }
}

namespace elements_access_suite {
    TEST(elements_access, at) {
        s21::map<int, double> map{{1, 1}, {2, 2}, {3, 3}};
        ASSERT_EQ(map.at(1), 1);
        ASSERT_EQ(map.at(2), 2);
        ASSERT_EQ(map.at(3), 3);

        map.at(1) = 4;
        ASSERT_EQ(map.at(1), 4);

        EXPECT_THROW(map.at(4), std::out_of_range);
    }

    TEST(elements_access, square_brackets) {
        s21::map<int, double> map{{1, 1}, {2, 2}, {3, 3}};
        ASSERT_EQ(map[1], 1);
        ASSERT_EQ(map[2], 2);
        ASSERT_EQ(map[3], 3);

        map[1] = 4;
        ASSERT_EQ(map[1], 4);

        EXPECT_THROW(map[4], std::out_of_range);
    }    
}

namespace additional_functions_suite {
    TEST(additional_functions, merge) {
        s21::map<int, double> map1{{1, 1}, {2, 2}, {3, 3}};
        s21::map<int, double> map2{{4, 4}, {5, 5}, {6, 6}};
        map1.merge(map2);
        ASSERT_EQ(map1.size(), 6);
    }

    TEST(additional_functions, swap) {
        s21::map<int, double> map1{{1, 1}, {2, 2}, {3, 3}};
        s21::map<int, double> map2{{4, 4}, {5, 5}, {6, 6}, {7, 7}};
        map1.swap(map2);
        ASSERT_EQ(map1.size(), 4);
        ASSERT_EQ(map2.size(), 3);
        ASSERT_EQ(map1[4], 4);
        ASSERT_EQ(map1[7], 7);
        ASSERT_EQ(map2[1], 1);
        EXPECT_THROW(map2[4], std::out_of_range);
    }

}

namespace iterator_suite {
    TEST(iterators, map_iterator) {
      s21::map<int, double> map;
      int keys [] = {1, 2, 3};
      double values [] = {4, 5, 6};
      map.insert(1, 4);
      map.insert(2, 5);
      map.insert(3, 6);
      int i = 0;
      for (auto it = map.begin(); it != map.end(); ++it) {
        ASSERT_EQ((*it).first, keys[i]);
        ASSERT_EQ((*it).second, values[i]);
        i++;
      }
    }

    
}

int main(int argc, char *argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}