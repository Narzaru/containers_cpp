#include <gtest/gtest.h>
#include "s21_map.h"
#include <iostream>

using namespace std;

namespace constructors_suite {
    TEST(constructors, empty_constructor) {
        s21::map<int, double> map;
        ASSERT_EQ(map.size(), 0);
    }
}

namespace insert_suite {
    TEST(insert, insert_several) {
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
}

int main(int argc, char *argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}