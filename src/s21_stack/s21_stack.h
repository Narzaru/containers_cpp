#ifndef SRC_S21_STACK_S21_STACK_H_
#define SRC_S21_STACK_S21_STACK_H_

#include "s21_vector/s21_vector.h"
#include <gtest/internal/gtest-death-test-internal.h>

namespace s21 {
template <typename T>
class stack : private s21::vector<T> {
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

 public:
  stack() : vector<value_type>() {}
  stack(const std::initializer_list<value_type> &list)
      : vector<value_type>(list) {}
  stack(const stack &other) : vector<value_type>(other) {}
  stack(stack &&other) noexcept : vector<value_type>(std::move(other)) {}
  ~stack() = default;
  stack &operator=(const stack &other) { vector<value_type>::operator=(other); }
  stack &operator=(stack &&other) noexcept { vector<value_type>::operator=(other); }

  [[nodiscard]] const_reference top() { return vector<value_type>::back(); }

  [[nodiscard]] bool empty() { return vector<value_type>::empty(); }
  size_type size() { return vector<value_type>::size(); }

  void push(const_reference value) { vector<value_type>::push_back(value); }
  void pop() { return vector<value_type>::pop_back(); }
  void swap(stack &other) { vector<value_type>::swap(other); }
};
}  // namespace s21

#endif  // SRC_S21_STACK_S21_STACK_H_
