#include <gtest/gtest.h>

#include "s21_containers.h"

namespace constructors_suite {
TEST(constructors, base_constructor_test_1) {
  s21::stack<int> stk1;
  ASSERT_EQ(stk1.size(), 0);
}

TEST(constructors, initializer_list_constructor_test_1) {
  s21::stack<int> stk({1, 2, 3, 4});
  ASSERT_EQ(stk.size(), 4);
  ASSERT_EQ(stk.top(), 4);
  stk.pop();
  ASSERT_EQ(stk.top(), 3);
  stk.pop();
  ASSERT_EQ(stk.top(), 2);
  stk.pop();
  ASSERT_EQ(stk.top(), 1);
}

TEST(constructors, copy_constructor_test_1) {
  s21::stack<int> stk1;
  s21::stack<int> stk2(stk1);
  ASSERT_EQ(stk1.size(), 0);
}

TEST(constructors, copy_constructor_test_2) {
  s21::stack<int> stk1({1, 2, 3, 4});
  s21::stack<int> stk2(stk1);
  ASSERT_EQ(stk2.size(), 4);
  ASSERT_EQ(stk1.top(), stk2.top());
  stk1.pop(), stk2.pop();
  ASSERT_EQ(stk1.top(), stk2.top());
  stk1.pop(), stk2.pop();
  ASSERT_EQ(stk1.top(), stk2.top());
  stk1.pop(), stk2.pop();
  ASSERT_EQ(stk1.top(), stk2.top());
}

TEST(constructors, move_constructor_test_1) {
  s21::stack<int> stk1({1, 2, 3, 4});
  s21::stack<int> stk2(std::move(stk1));
  ASSERT_EQ(stk1.size(), 0);
  ASSERT_EQ(stk2.size(), 4);
  ASSERT_EQ(stk2.top(), 4);
  stk2.pop();
  ASSERT_EQ(stk2.top(), 3);
  stk2.pop();
  ASSERT_EQ(stk2.top(), 2);
  stk2.pop();
  ASSERT_EQ(stk2.top(), 1);
}
}  // namespace constructors_suite

namespace operators_suite {
TEST(operators, copy_assignment_operator_test_1) {
  s21::stack<int> stk1({1, 2, 3, 4});
  s21::stack<int> stk2 = stk1;
  ASSERT_EQ(stk2.size(), 4);
  ASSERT_EQ(stk1.top(), stk2.top());
  stk1.pop(), stk2.pop();
  ASSERT_EQ(stk1.top(), stk2.top());
  stk1.pop(), stk2.pop();
  ASSERT_EQ(stk1.top(), stk2.top());
  stk1.pop(), stk2.pop();
  ASSERT_EQ(stk1.top(), stk2.top());
}

TEST(operators, copy_assignment_operator_test_2) {
  s21::stack<int> stk1;
  s21::stack<int> stk2 = stk1;
  ASSERT_EQ(stk1.size(), 0);
}

TEST(operators, move_assignment_operator_test_2) {
  s21::stack<int> stk1({1, 2, 3, 4});
  s21::stack<int> stk2 = std::move(stk1);
  ASSERT_EQ(stk1.size(), 0);
  ASSERT_EQ(stk2.size(), 4);
  ASSERT_EQ(stk2.top(), 4);
  stk2.pop();
  ASSERT_EQ(stk2.top(), 3);
  stk2.pop();
  ASSERT_EQ(stk2.top(), 2);
  stk2.pop();
  ASSERT_EQ(stk2.top(), 1);
}
}  // namespace operators_suite

namespace top_suite {
TEST(top, top_test_1) {
  s21::stack<int> stk({1, 2, 3, 4, 5, 6});
  ASSERT_EQ(stk.top(), 6);
  stk.pop();
  ASSERT_EQ(stk.top(), 5);
}
}  // namespace top_suite

namespace empty_suite {
TEST(empty, empty_test_1) {
  s21::stack<int> stk({1});
  ASSERT_FALSE(stk.empty());
  stk.pop();
  ASSERT_TRUE(stk.empty());
}
}  // namespace empty_suite

namespace size_suite {
TEST(size, size_test_1) {
  s21::stack<int> stk({1, 2, 3, 4, 5, 6});
  ASSERT_EQ(stk.size(), 6);
  stk.pop();
  ASSERT_EQ(stk.size(), 5);
}

}  // namespace size_suite

namespace push_suite {
TEST(push, push_test_1) {
  s21::stack<int> stk({1, 2, 3, 4, 5, 6});
  ASSERT_NO_THROW(stk.push(7));
  ASSERT_EQ(stk.size(), 7);
  ASSERT_EQ(stk.top(), 7);
}

TEST(push, push_test_2) {
  s21::stack<int> stk;
  ASSERT_NO_THROW(stk.push(7));
  ASSERT_EQ(stk.size(), 1);
  ASSERT_EQ(stk.top(), 7);
}
}  // namespace push_suite

namespace pop_suite {
TEST(pop, pop_test_1) {
  s21::stack<int> stk({1, 2, 3});
  ASSERT_EQ(stk.size(), 3);
  ASSERT_NO_THROW(stk.pop());
  ASSERT_EQ(stk.size(), 2);
}

TEST(pop, pop_test_2) {
  s21::stack<int> stk;
  ASSERT_NO_THROW(stk.pop());
  ASSERT_EQ(stk.size(), -1UL);
}
}  // namespace pop_suite

namespace swap_suite {
TEST(swap, swap_test_1) {
  s21::stack<int> stk1({1});
  s21::stack<int> stk2({1, 2, 3});
  ASSERT_NO_THROW(stk1.swap(stk2));
  ASSERT_EQ(stk1.size(), 3);
  ASSERT_EQ(stk2.size(), 1);
}
}  // namespace swap_suite
