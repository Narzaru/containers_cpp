#ifndef SRC_S21_ARRAY_S21_ARRAY_H_
#define SRC_S21_ARRAY_S21_ARRAY_H_

#include <cstddef>
#include <initializer_list>
#include <array>

namespace s21 {
template <typename T, std::size_t length>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &other);
  array(array &&other);
  ~array();
  array &operator=(array &other);
  array &operator=(array &&other);

  reference at(size_type position);
  reference operator[](size_type);
  const_reference front();
  const_reference back();
  iterator data();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void swap(array &other);
  void fill(const_reference value);
};
}  // namespace s21

#endif  // SRC_S21_ARRAY_S21_ARRAY_H_
