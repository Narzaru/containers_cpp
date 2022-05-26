#ifndef SRC_S21_ARRAY_S21_ARRAY_H_
#define SRC_S21_ARRAY_S21_ARRAY_H_

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

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

  array() = default;
  array(std::initializer_list<value_type> const &items) {
    if (items.size() > length) {
      throw std::length_error("size of items is out of range");
    }
    std::copy(items.begin(), items.end(), array_);
  }
  array(const array &other) = default;
  array(array &&other) noexcept = default;
  ~array() = default;
  array &operator=(array const &other) = default;
  array &operator=(array &&other) noexcept = default;

  reference at(size_type position) {
    if (position >= length) {
      throw std::out_of_range("position is out of range");
    }
    return *(begin() + position);
  }

  const_reference at(size_type position) const {
    return const_cast<array *>(this)->at(position);
  }

  reference operator[](size_type position) { return at(position); }
  const_reference operator[](size_type position) const { return at(position); }
  const_reference front() const { return *begin(); }
  const_reference back() const { return *(end() - 1); }
  iterator data() { return array_; }
  const_iterator data() const { return array_; }

  iterator begin() { return iterator(data()); }
  iterator end() { return iterator(data() + length); }
  const_iterator begin() const { return const_iterator(data()); }
  const_iterator end() const { return const_iterator(data() + length); }
  [[nodiscard]] bool empty() const { return size() == 0; }
  [[nodiscard]] size_type size() const { return length; }
  [[nodiscard]] size_type max_size() const {
    return size();
  }

  void swap(array &other) { std::swap(*this, other); }
  void fill(const_reference value) { std::fill(begin(), end(), value); }

 private:
  alignas(T) T array_[sizeof(T) * length] = {};
};
}  // namespace s21

#endif  // SRC_S21_ARRAY_S21_ARRAY_H_
