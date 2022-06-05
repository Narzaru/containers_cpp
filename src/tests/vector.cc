#include <gtest/gtest.h>

#include <algorithm>

#include "s21_containers.h"

namespace vector_constructors_suite {
TEST(constructors, base_constructor_test) {
  s21::vector<double> vec;
  ASSERT_TRUE(vec.empty());
}

TEST(constructors, size_constructor_test_1) {
  s21::vector<double> vec(10);
  ASSERT_EQ(vec.size(), 10);
  ASSERT_EQ(vec.capacity(), 10);
}

TEST(constructors, size_constructor_test_2) {
  s21::vector<double> vec(0);
  ASSERT_TRUE(vec.empty());
}

TEST(constructors, size_constructor_test_3) {
  ASSERT_THROW(s21::vector<double> vec(-1), std::length_error);
}

TEST(constructors, size_constructor_test_4) {
  ASSERT_THROW(
      s21::vector<double> vec(
          std::numeric_limits<unsigned long>::max() / sizeof(double) + 1),
      std::length_error);
}

TEST(constructors, initializer_list_constructor_test_1) {
  s21::vector<double> vec({1, 2, 3, 4});
  s21::vector<double> sample(4);
  sample[0] = 1;
  sample[1] = 2;
  sample[2] = 3;
  sample[3] = 4;
  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec.capacity(), 4);
  ASSERT_TRUE(std::equal(sample.begin(), sample.end(), vec.begin()));
}

TEST(constructors, initializer_list_constructor_test_2) {
  s21::vector<double> vec({});
  ASSERT_TRUE(vec.empty());
}

TEST(constructors, copy_constructor_test_1) {
  s21::vector<int> vec_1({1, 2, 3, 4});
  s21::vector<int> vec_2(vec_1);
  s21::vector<int> example({1, 2, 3, 4});
  ASSERT_EQ(vec_2.size(), example.size());
  ASSERT_EQ(vec_2.capacity(), example.capacity());
  ASSERT_TRUE(std::equal(example.begin(), example.end(), vec_2.begin()));
}

TEST(constructors, copy_constructor_test_2) {
  s21::vector<int> vec_1;
  s21::vector<int> vec_2(vec_1);
  vec_2.begin();  // warning suppression
  ASSERT_EQ(vec_2.size(), 0);
  ASSERT_EQ(vec_2.capacity(), 0);
}

TEST(constructors, move_constructor_test_1) {
  s21::vector<double> vec_1({1, 2});
  s21::vector<double> vec_2(std::move(vec_1));
  s21::vector<double> sample({1, 2});
  ASSERT_TRUE(std::equal(
      sample.begin(), sample.end(), vec_2.begin(), [](double a, double b) {
        return (std::abs(a - b) < std::numeric_limits<float>::epsilon());
      }));
}

TEST(constructors, move_constructor_test_2) {
  s21::vector<double> vec_1;
  s21::vector<double> vec_2(std::move(vec_1));
  ASSERT_TRUE(vec_2.empty());
}

}  // namespace vector_constructors_suite

namespace vector_insert_suite {
TEST(insert, insert_1) {
  s21::vector<int> vec({1, 2, 3, 5, 6});
  vec.insert(vec.begin() + 3, 4);
  s21::vector<int> example({1, 2, 3, 4, 5, 6});
  ASSERT_EQ(vec.size(), 6);
  ASSERT_EQ(vec.capacity(), 10);
  ASSERT_TRUE(std::equal(example.begin(), example.end(), vec.begin()));
}

TEST(insert, insert_2) {
  s21::vector<int> vec;
  s21::vector<int> example({0});
  vec.insert(vec.begin(), 0);
  ASSERT_EQ(vec.size(), 1);
  ASSERT_EQ(vec.capacity(), 1);
  ASSERT_TRUE(std::equal(example.begin(), example.end(), vec.begin()));
}

TEST(insert, insert_3) {
  s21::vector<int> vec;
  s21::vector<int> example({2, 1, 0});
  vec.insert(vec.begin(), 0);
  vec.insert(vec.begin(), 1);
  vec.insert(vec.begin(), 2);
  ASSERT_EQ(vec.size(), 3);
  ASSERT_EQ(vec.capacity(), 4);
  ASSERT_TRUE(std::equal(example.begin(), example.end(), vec.begin()));
}

TEST(insert, insert_4) {
  s21::vector<int> vec;
  s21::vector<int> example({0, 1});
  vec.insert(vec.begin(), 0);
  vec.insert(vec.begin() + 1, 1);
  ASSERT_EQ(vec.size(), 2);
  ASSERT_EQ(vec.capacity(), 2);
  ASSERT_TRUE(std::equal(example.begin(), example.end(), vec.begin()));
}

TEST(insert, insert_5) {
  s21::vector<int> vec({1, 2, 3});
  s21::vector<int> example({0, 1, 1, 2, 3});
  vec.insert(vec.begin(), 0);
  vec.insert(vec.begin() + 1, 1);
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec.capacity(), 6);
  ASSERT_TRUE(std::equal(example.begin(), example.end(), vec.begin()));
}
}  // namespace vector_insert_suite

namespace vector_erase_suite {
TEST(erase, erase_1) {
  s21::vector<int> vec({1, 1, 2, 3, 4});
  s21::vector<int> example({1, 2, 3, 4});
  vec.erase(vec.begin());
  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec.capacity(), 5);
  ASSERT_TRUE(std::equal(example.begin(), example.end(), vec.begin()));
}

TEST(erase, erase_2) {
  s21::vector<int> vec({1, 1, 1, 2, 1});
  s21::vector<int> example({1, 1, 1, 1});
  vec.erase(vec.begin() + 3);
  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec.capacity(), 5);
  ASSERT_TRUE(std::equal(example.begin(), example.end(), vec.begin()));
}

TEST(erase, erase_3) {
  s21::vector<int> vec;
  ASSERT_ANY_THROW(vec.erase(vec.begin()));
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 0);
}

TEST(erase, erase_4) {
  s21::vector<int> vec({1});
  ASSERT_ANY_THROW(vec.erase(vec.begin() + 1));
  ASSERT_EQ(vec.size(), 1);
  ASSERT_EQ(vec.capacity(), 1);
  vec.erase(vec.begin());
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 1);
  ASSERT_ANY_THROW(vec.erase(vec.begin()));
}
}  // namespace vector_erase_suite

namespace vector_clear_suite {
TEST(clear, clear_1) {
  s21::vector<int> vec({1, 2, 3});
  ASSERT_NO_THROW(vec.clear());
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 0);
  ASSERT_NO_THROW(vec.clear());
}
}  // namespace vector_clear_suite

namespace vector_push_back_suite {
TEST(push_back, push_back_1) {
  s21::vector<int> vec;
  s21::vector<int> example({0, 2, 4, 16});
  ASSERT_NO_THROW(vec.push_back(0));
  ASSERT_NO_THROW(vec.push_back(2));
  ASSERT_NO_THROW(vec.push_back(4));
  ASSERT_NO_THROW(vec.push_back(16));
  ASSERT_EQ(vec.size(), 4);
  ASSERT_EQ(vec.capacity(), 4);
  ASSERT_TRUE(std::equal(example.begin(), example.end(), vec.begin()));
}

TEST(push_back, push_back_2) {
  s21::vector<int> vec(5);
  s21::vector<int> example({0, 0, 0, 0, 0, 0, 2, 2, 0});
  ASSERT_NO_THROW(vec.push_back(0));
  ASSERT_NO_THROW(vec.push_back(2));
  ASSERT_NO_THROW(vec.push_back(2));
  ASSERT_NO_THROW(vec.push_back(0));
  ASSERT_EQ(vec.size(), 9);
  ASSERT_EQ(vec.capacity(), 10);
  ASSERT_TRUE(std::equal(example.begin(), example.end(), vec.begin()));
}
}  // namespace vector_push_back_suite

namespace vector_pop_back_suite {
TEST(pop_back, pop_back_1) {
  s21::vector<int> vec({1, 2, 3});
  vec.pop_back();
  vec.pop_back();
  ASSERT_EQ(vec.size(), 1);
  ASSERT_EQ(vec.capacity(), 3);
  ASSERT_EQ(vec[0], 1);
}

TEST(pop_back, pop_back_2) {
  s21::vector<int> vec;
  vec.pop_back();
  ASSERT_EQ(vec.size(), -1UL);
  ASSERT_EQ(vec.capacity(), 0);
}
}  // namespace vector_pop_back_suite

namespace vector_swap_suite {
TEST(swap, swap_1) {
  s21::vector<int> vec_1({1, 2, 3});
  s21::vector<int> vec_2({1, 2, 4, 5, 6});

  s21::vector<int> example_1({1, 2, 3});
  s21::vector<int> example_2({1, 2, 4, 5, 6});

  vec_1.swap(vec_2);
  ASSERT_EQ(vec_1.size(), 5);
  ASSERT_EQ(vec_1.capacity(), 5);

  ASSERT_EQ(vec_2.size(), 3);
  ASSERT_EQ(vec_2.capacity(), 3);

  ASSERT_TRUE(std::equal(example_1.begin(), example_1.end(), vec_2.begin()));
  ASSERT_TRUE(std::equal(example_2.begin(), example_2.end(), vec_1.begin()));
}
}  // namespace vector_swap_suite

namespace vector_empty_suite {
TEST(empty, empty_1) {
  s21::vector<int> vec;
  ASSERT_TRUE(vec.empty());
}

TEST(empty, empty_2) {
  s21::vector<int> vec({});
  ASSERT_TRUE(vec.empty());
}

TEST(empty, empty_3) {
  s21::vector<int> vec({});
  vec.push_back(4);
  ASSERT_FALSE(vec.empty());
}
}  // namespace vector_empty_suite

namespace vector_size_capacity_suite {
TEST(size_capacity, size_capacity_1) {
  s21::vector<int> vec;
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 0);
}

TEST(size_capacity, size_capacity_2) {
  s21::vector<int> vec({1});
  vec.push_back(1);
  ASSERT_EQ(vec.size(), 2);
  ASSERT_EQ(vec.capacity(), 2);
}

TEST(size_capacity, size_capacity_3) {
  s21::vector<int> vec({1});
  vec.push_back(1);
  vec.push_back(1);
  ASSERT_EQ(vec.size(), 3);
  ASSERT_EQ(vec.capacity(), 4);
}

TEST(size_capacity, max_size_1) {
  s21::vector<long> vec;
  ASSERT_EQ(vec.max_size(), std::numeric_limits<long>::max() / sizeof(long));
}
}  // namespace vector_size_capacity_suite

namespace vector_resize_suite {
TEST(resize, reserve_1) {
  s21::vector<int> vec;
  vec.reserve(100);
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 100);
}

TEST(resize, reserve_2) {
  s21::vector<int> vec(100);
  ASSERT_NO_THROW(vec.reserve(0));
  ASSERT_EQ(vec.size(), 100);
  ASSERT_EQ(vec.capacity(), 100);
}

TEST(resize, reserve_3) {
  s21::vector<int> vec({1, 2, 3, 4, 5});
  s21::vector<int> example({1, 2, 3, 4, 5});
  vec.reserve(100);
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec.capacity(), 100);
  ASSERT_TRUE(std::equal(example.begin(), example.end(), vec.begin()));
}

TEST(resize, shrink_1) {
  s21::vector<int> vec(5);
  s21::vector<int> example({0, 0, 0, 0, 0, 8});
  vec.push_back(8);
  ASSERT_NO_THROW(vec.shrink_to_fit());
  ASSERT_EQ(vec.size(), 6);
  ASSERT_EQ(vec.capacity(), 6);
  ASSERT_TRUE(std::equal(example.begin(), example.end(), vec.begin()));
}

TEST(resize, shrink_2) {
  s21::vector<int> vec(5);
  ASSERT_NO_THROW(vec.shrink_to_fit());
  ASSERT_EQ(vec.size(), 5);
  ASSERT_EQ(vec.capacity(), 5);
}

TEST(resize, shrink_3) {
  s21::vector<int> vec;
  ASSERT_NO_THROW(vec.shrink_to_fit());
  ASSERT_EQ(vec.size(), 0);
  ASSERT_EQ(vec.capacity(), 0);
}
}  // namespace vector_resize_suite

namespace vector_access_suite {
TEST(access, at_1) {
  s21::vector<int> vec;
  ASSERT_ANY_THROW(vec.at(0));
}

TEST(access, at_2) {
  s21::vector<int> vec({1, 2});
  ASSERT_NO_THROW(vec.at(0) = 2);
  ASSERT_EQ(vec[0], 2);
}

TEST(access, operator_bracket_2) {
  s21::vector<int> vec({1, 2});
  ASSERT_NO_THROW(vec[0] = 2);
  ASSERT_EQ(vec.at(0), 2);
}

TEST(access, front_back_1) {
  s21::vector<int> vec({1, 2, 3, 4});
  ASSERT_EQ(vec.front(), 1);
  ASSERT_EQ(vec.back(), 4);
}

TEST(access, front_back_2) {
  s21::vector<int> vec({1});
  ASSERT_EQ(vec.front(), 1);
  ASSERT_EQ(vec.back(), 1);
}

TEST(access, begin_end_1) {
  s21::vector<int> vec({1, 2, 3, 4});
  ASSERT_EQ(*vec.begin(), 1);
  ASSERT_EQ(*(vec.end() - 1), 4);
}

TEST(access, begin_end_2) {
  s21::vector<int> vec({1});
  ASSERT_EQ(*vec.begin(), 1);
  ASSERT_EQ(*(vec.end() - 1), 1);
}
}  // namespace vector_access_suite

template <typename T>
void test(T &&val) {
  std::cout << val;
}

namespace emplace_suite {
TEST(emplace, emplace_1) {
  s21::vector<s21::vector<int>> vec;
  vec.emplace(vec.begin(), std::initializer_list<int>({1, 2, 3, 4}));
  ASSERT_EQ(vec[0][3], 4);
}

TEST(emplace, emplace_2) {
  s21::vector<int> vec{1, 2, 3, 4};
  vec.emplace(vec.begin(), 0);
  ASSERT_EQ(vec[0], 0);
}

TEST(emplace, emplace_3) {
  s21::vector<s21::vector<int>> vec;
  vec.emplace_back(std::initializer_list<int>({1, 2, 3, 4}));
  ASSERT_EQ(vec[0][3], 4);
}

TEST(emplace, emplace_4) {
  s21::vector<int> vec{1, 2, 3, 4};
  vec.emplace_back(5);
  ASSERT_EQ(vec.back(), 5);
}
}  // namespace emplace_suite
