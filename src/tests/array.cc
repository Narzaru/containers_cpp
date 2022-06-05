#include <cstddef>
#include <gtest/gtest.h>

#include <algorithm>
#include <array>

#include "s21_array/s21_array.h"
#include "s21_containersplus.h"

namespace array_constructors_suite {
TEST(array_constructors, base_constructor_1) {
  s21::array<int, 16> array;
  ASSERT_NO_THROW(array[15]);
}

TEST(array_constructors, initialize_list_constructor_1) {
  s21::array<int, 16> array({1, 2, 3, 4});
  std::array<int, 16> stdarray({1, 2, 3, 4});
  ASSERT_TRUE(
      std::equal(stdarray.begin(), stdarray.begin() + 4, array.begin()));
}

TEST(array_constructors, initialize_list_constructor_2) {
  s21::array<int, 16> array({});
  ASSERT_NO_THROW(array[15]);
}

TEST(array_constructors, copy_constructor) {
  s21::array<int, 16> array_1({1, 2, 3, 4});
  s21::array<int, 16> array_2(array_1);
  std::array<int, 16> stdarray_1({1, 2, 3, 4});
  std::array<int, 16> stdarray_2(stdarray_1);
  ASSERT_TRUE(
      std::equal(stdarray_2.begin(), stdarray_2.begin() + 4, array_2.begin()));
  ASSERT_EQ(stdarray_2.size(), array_2.size());
}

TEST(array_constructors, move_constructor_1) {
  s21::array<int, 16> array_1({1, 2, 3, 4});
  s21::array<int, 16> array_2(std::move(array_1));
  std::array<int, 16> stdarray_1({1, 2, 3, 4});
  std::array<int, 16> stdarray_2(std::move(stdarray_1));
  ASSERT_TRUE(
      std::equal(stdarray_2.begin(), stdarray_2.begin() + 4, array_2.begin()));
  ASSERT_EQ(stdarray_1.size(), array_1.size());
  ASSERT_TRUE(
      std::equal(stdarray_1.begin(), stdarray_1.begin() + 4, array_1.begin()));
}

TEST(array_constructors, copy_assignment_1) {
  s21::array<int, 16> array_1({1, 2, 3, 4});
  s21::array<int, 16> array_2 = array_1;
  std::array<int, 16> stdarray_1({1, 2, 3, 4});
  std::array<int, 16> stdarray_2 = stdarray_1;
  ASSERT_TRUE(
      std::equal(stdarray_2.begin(), stdarray_2.begin() + 4, array_2.begin()));
  ASSERT_EQ(stdarray_1.size(), array_1.size());
  ASSERT_TRUE(
      std::equal(stdarray_1.begin(), stdarray_1.begin() + 4, array_1.begin()));
}

TEST(array_constructors, move_assignment_1) {
  s21::array<int, 16> array_1({1, 2, 3, 4});
  s21::array<int, 16> array_2 = std::move(array_1);
  std::array<int, 16> stdarray_1({1, 2, 3, 4});
  std::array<int, 16> stdarray_2 = std::move(stdarray_1);
  ASSERT_TRUE(
      std::equal(stdarray_2.begin(), stdarray_2.begin() + 4, array_2.begin()));
  ASSERT_EQ(stdarray_1.size(), array_1.size());
  ASSERT_TRUE(
      std::equal(stdarray_1.begin(), stdarray_1.begin() + 4, array_1.begin()));
}
}  // namespace array_constructors_suite

namespace array_accessors_suie {
TEST(accessors, at_1) {
  const s21::array<int, 16> array{1, 2, 3};
  const std::array<int, 16> stdarray{1, 2, 3};
  ASSERT_EQ(array.at(0), stdarray.at(0));
}

TEST(accessors, at_2) {
  const s21::array<int, 16> array{1, 2, 3};
  ASSERT_ANY_THROW(array.at(16));
}

TEST(accessors, operator_square_brackets_1) {
  const s21::array<int, 16> array{1, 2, 3};
  const std::array<int, 16> stdarray{1, 2, 3};
  ASSERT_EQ(array[2], stdarray[2]);
}

TEST(accessors, operator_square_brackets_2) {
  const s21::array<int, 16> array{1, 2, 3};
  ASSERT_ANY_THROW(array[16]);
}

TEST(accessors, front_back_1) {
  const s21::array<int, 3> array{1, 2, 3};
  const std::array<int, 3> stdarray{1, 2, 3};
  ASSERT_EQ(array.front(), stdarray.front());
  ASSERT_EQ(array.back(), stdarray.back());
}

TEST(accessors, begin_end_1) {
  s21::array<int, 3> array{1, 2, 3};
  std::array<int, 3> stdarray{1, 2, 3};
  ASSERT_EQ(*(array.end() - 1), *(stdarray.end() - 1));
  ASSERT_EQ(*array.begin(), *stdarray.begin());
}
}  // namespace array_accessors_suie

namespace array_size_suite {
TEST(size, empty_1) {
  s21::array<int, 1> array;
  ASSERT_FALSE(array.empty());
}

TEST(size, size_1) {
  s21::array<int, 1> array;
  ASSERT_EQ(array.size(), 1);
}

TEST(size, max_size_1) {
  s21::array<int, 1> array;
  std::array<int, 1> stdarray;
  ASSERT_EQ(array.max_size(), stdarray.max_size());
}
}  // namespace array_size_suite

namespace array_modifiers_suite {
TEST(array_modifiers, swap_1) {
  s21::array<int, 5> array_1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> array_2 = {5, 4, 3, 2, 1};
  ASSERT_NO_THROW(array_1.swap(array_2));
  for (std::size_t i = 0; i < array_1.size(); ++i) {
    ASSERT_EQ(array_1[i], array_2[4 - i]);
  }
}

TEST(array_modifiers, fill_1) {
  s21::array<int, 5> array_1 = {1, 2, 3, 4, 5};
  array_1.fill(0);
  for (auto item : array_1) {
    ASSERT_EQ(item, 0);
  }
}
}  // namespace array_modifiers_suite

namespace array_swap_fill_suite {
TEST(swap_fill, swap_1) {
  s21::array<int, 16> array_1({1, 2, 3, 4});
  s21::array<int, 16> array_2({1, 2, 3, 4, 5, 6, 7, 8});
  std::array<int, 16> stdarray_1({1, 2, 3, 4});
  std::array<int, 16> stdarray_2({1, 2, 3, 4, 5, 6, 7, 8});
  array_1.swap(array_2);
  stdarray_1.swap(stdarray_2);
  ASSERT_TRUE(
      std::equal(stdarray_2.begin(), stdarray_2.begin() + 8, array_2.begin()));
  ASSERT_EQ(stdarray_1.size(), array_1.size());
  ASSERT_TRUE(
      std::equal(stdarray_1.begin(), stdarray_1.begin() + 4, array_1.begin()));
}
}  // namespace array_swap_fill_suite
