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
  reference operator[](size_type position) noexcept;
  const_reference operator[](size_type position) const noexcept;
  reference front() noexcept;
  const_reference front() const noexcept;
  reference back() noexcept;
  const_reference back() const noexcept;

  iterator data() noexcept;
  const_iterator data() const noexcept;
  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  bool empty() const noexcept;
  [[nodiscard]] size_type size() const noexcept;
  [[nodiscard]] size_type max_size() const noexcept;
  void reserve(size_type new_capacity);
  [[nodiscard]] size_type capacity() const noexcept;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  // This strange entry works like this.
  // Somewhere in a programm:
  // vector.emplace_back(10, 20.0) =>
  // push_back(object_constructor(std::forward<Args>(10, 20.0)...)) =>
  // push_back(object_constructor(std::forward<int &>(10), std::forward<double
  // &>(10));
  // This means that the object is constructed at the call site without
  // unnecessary copying.

  // Args && - not rvalue reference.
  // https://clck.ru/iNGcb Reference collapsing
  template <typename... Args>
  inline iterator emplace(iterator pos, Args &&...args) {
    return insert(pos, value_type(std::forward<Args>(args)...));
  }

  template <typename... Args>
  inline void emplace_back(Args &&...args) {
    push_back(value_type(std::forward<Args>(args)...));
  }

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
