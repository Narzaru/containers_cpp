#ifndef SRC_S21_VECTOR_S21_VECTOR_H_
#define SRC_S21_VECTOR_S21_VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  vector();
  explicit vector(size_type capacity);
  vector(std::initializer_list<value_type> const &list);
  vector(const vector &other);
  vector(vector &&other) noexcept;
  ~vector();
  vector<value_type> &operator=(const vector &other);
  vector<value_type> &operator=(vector &&other) noexcept;

  reference at(size_type position);
  const_reference at(size_type position) const;
  reference operator[](size_type position);
  const_reference operator[](size_type position) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;

  iterator data();
  const_iterator data() const;
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() const;
  [[nodiscard]] size_type size() const;
  [[nodiscard]] size_type max_size() const;
  void reserve(size_type new_capacity);
  [[nodiscard]] size_type capacity() const;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

 private:
  iterator array_{};
  size_type size_{};
  size_type capacity_{};

  void realloc_array(size_type new_capacity);
  void realloc_and_copy(size_type new_capacity);
};

}  // namespace s21

#include "s21_vector.inc"

#endif  // SRC_S21_VECTOR_S21_VECTOR_H_
