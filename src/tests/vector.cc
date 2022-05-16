#include <gtest/gtest.h>

#include "s21_containers.h"

namespace constructors_suite {
TEST(constructors, empty_constructor) {
  s21::vector<double> vec;
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 0);
}

TEST(constructors, size_constructor_1) {
  s21::vector<double> vec(10);
  ASSERT_EQ(vec.size(), 10);
  ASSERT_EQ(vec.capacity(), 10);
}

// TODO(bgreydon) add more tests with 0 size
TEST(constructors, size_constructor_2) {
  s21::vector<double> vec(0);
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 0);
}

// TODO(bgreydon) add more tests with max size size
TEST(constructors, size_constructor_3) {
  ASSERT_THROW(s21::vector<double> vec(-1), std::length_error);
}

TEST(constructors, initializer_list_constructor_1) {
  s21::vector<double> vec({1, 2, 3, 4});
  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec.capacity(), 4);
}

// TODO(bgreydon) add more tests with 0 size
TEST(constructors, initializer_list_constructor_2) {
  s21::vector<double> vec({});
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 0);
}

}  // namespace constructors_suite


namespace insert_suite {
TEST(insert, insert_1) {
  s21::vector<int> vec({1, 2, 3, 5, 6});
  vec.insert(vec.begin() + 3, 4);
  ASSERT_EQ(vec.size(), 6);
  ASSERT_EQ(vec.capacity(), 10);
}

TEST(insert, insert_2) {
  s21::vector<int> vec;
  vec.insert(vec.begin(), 0);
  ASSERT_EQ(vec.size(), 1);
  ASSERT_EQ(vec.capacity(), 1);
}

TEST(insert, insert_3) {
  s21::vector<int> vec;
  vec.insert(vec.begin(), 0);
  vec.insert(vec.begin(), 1);
  vec.insert(vec.begin(), 2);
  ASSERT_EQ(vec.size(), 3);
  ASSERT_EQ(vec.capacity(), 4);
}

TEST(insert, insert_4) {
  s21::vector<int> vec;
  vec.insert(vec.begin(), 0);
  vec.insert(vec.begin() + 1, 1);
  ASSERT_EQ(vec.size(), 2);
  ASSERT_EQ(vec.capacity(), 2);
}

TEST(insert, insert_4) {
  s21::vector<int> vec;
  vec.insert(vec.begin(), 0);
  vec.insert(vec.begin() + 1, 1);
  ASSERT_EQ(vec.size(), 2);
  ASSERT_EQ(vec.capacity(), 2);
}
};
