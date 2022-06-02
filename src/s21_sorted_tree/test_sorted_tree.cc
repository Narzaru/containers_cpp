#include <gtest/gtest.h>
#include "s21_sorted_tree.h"
#include <iostream>

using namespace std;

namespace constructors_suite {
    TEST(constructors, empty_constructor) {
        s21::sorted_tree<int, double> tree;
        ASSERT_EQ(tree.size(), 0);
    }
}

namespace insert_suite {
    TEST(insert, empty_constructor) {
        s21::sorted_tree<int, std::string> tree;
        tree.insert_pair(std::make_pair(1, "One_first"));
        tree.insert_pair(std::make_pair(2, "Two"));
        tree.insert_pair(std::make_pair(1, "One_second"));
        tree.insert_pair(std::make_pair(0, "Zero"));
        tree.insert_pair(std::make_pair(1, "One_third"));
        ASSERT_EQ(tree.size(), 5);
        // for (auto it = tree.begin(); it != tree.end(); ++it) {
        //   cout << (*it).first << endl;
        // }
        // auto it = tree.end();
        // for (; it != tree.begin(); --it) {
        //   cout << (*it).first << endl;
        // }
        // cout << (*it).first << endl;
    }
}

namespace erase_suite {
    TEST(insert, empty_constructor) {
        s21::sorted_tree<int, std::string> tree;
        tree.insert_pair(std::make_pair(1, "One_first"));
        tree.insert_pair(std::make_pair(2, "Two"));
        tree.insert_pair(std::make_pair(1, "One_second"));
        tree.insert_pair(std::make_pair(0, "Zero"));
        tree.insert_pair(std::make_pair(1, "One_third"));
        
        tree.erase(tree.find(1));
        ASSERT_EQ(tree.size(), 4);
        for (auto it = tree.begin(); it != tree.end(); ++it) {
          cout << (*it).first << endl;
        }
        tree.erase(tree.find(0));
        ASSERT_EQ(tree.size(), 3);
        for (auto it = tree.begin(); it != tree.end(); ++it) {
          cout << (*it).first << endl;
        }
    }
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}