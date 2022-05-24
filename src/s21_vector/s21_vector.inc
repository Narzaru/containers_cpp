#include "s21_vector.h"
#include <cstdint>

namespace s21 {

template <typename T>
vector<T>::vector() : vector(0) {}

template <typename T>
vector<T>::vector(size_type capacity)
    : array_(nullptr), size_(capacity), capacity_(capacity) {
  realloc_array(capacity);
}

template <typename T>
vector<T>::vector(std::initializer_list<T> const &list) : vector(list.size()) {
  std::copy(list.begin(), list.end(), array_);
}

template <typename T>
vector<T>::vector(const vector<T> &other) : vector(other.capacity_) {
  if (other.begin() != other.end()) {
    std::copy(other.begin(), other.end(), begin());
  }
  size_ = other.size_;
}

template <typename T>
vector<T>::vector(vector<T> &&other) noexcept
    : array_(other.array_), size_(other.size_), capacity_(other.capacity_) {
  other.array_ = nullptr;
  other.clear();
}

template <typename T>
vector<T>::~vector() {
  vector<T>::clear();
}

template <typename T>
vector<T> &vector<T>::operator=(const vector<T> &other) {
  if (capacity_ != other.capacity_) {
    capacity_ = other.capacity_;
    realloc_array(capacity_);
  }
  std::copy(other.begin(), other.end(), begin());
  size_ = other.size_;
  return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&other) noexcept {
  clear();
  array_ = other.array_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.array_ = nullptr;
  other.clear();
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type position) {
  return const_cast<vector<value_type>::reference>(
      const_cast<const vector<value_type> *>(this)->at(position));
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type position) const {
  if (position >= size_) {
    throw std::out_of_range("index is out of range");
  }
  if (capacity_ == 0) {
    throw std::length_error("vector is empty");
  }
  return array_[position];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type position) {
  return at(position);
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](
    size_type position) const {
  return at(position);
}

template <typename T>
typename vector<T>::reference vector<T>::front() {
  return *array_;
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  return *array_;
}

template <typename T>
typename vector<T>::reference vector<T>::back() {
  return *(array_ + (size_ - 1));
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  return *(array_ + (size_ - 1));
}

template <typename T>
typename vector<T>::iterator vector<T>::data() {
  return &front();
}

template <typename T>
typename vector<T>::const_iterator vector<T>::data() const {
  return &front();
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return &front();
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return &front();
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return &back() + 1;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return &back() + 1;
}

template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return PTRDIFF_MAX / sizeof(T);
}

template <typename T>
void vector<T>::reserve(vector<T>::size_type new_capacity) {
  if (new_capacity > max_size()) {
    throw std::length_error("trying to allocate as much as possible");
  }
  if (new_capacity > capacity_) {
    realloc_and_copy(new_capacity);
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    realloc_and_copy(size_);
  }
}

template <typename T>
void vector<T>::clear() {
  delete[] array_;
  array_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

// TODO(bgreydon) rework exceptions
template <typename T>
T *vector<T>::insert(T *pos, const T &value) {
  size_type insert_position = pos - array_;
  if (insert_position > size_) {
    throw std::out_of_range("insert position is out of range");
  }
  if (insert_position > max_size()) {
    throw std::length_error("trying to allocate as much as possible");
  }
  if (size_ + 1 > capacity_) {
    realloc_and_copy(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  for (size_type i = size_; i != insert_position; --i) {
    array_[i] = std::move(array_[i - 1]);
  }
  array_[insert_position] = std::move(value);
  size_ += 1;
  return pos;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type erase_position = pos - array_;
  if (empty()) {
    throw std::length_error("empty object erase");
  }
  if (erase_position > max_size()) {
    throw std::length_error("erase is greater than the max size of the vector");
  }
  if (erase_position >= size_) {
    throw std::out_of_range("erasing in an invalid range");
  }
  for (size_type i = erase_position; i < size_ - 1; ++i) {
    array_[i] = array_[i + 1];
  }
  size_ -= 1;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  insert(end(), value);
}

template <typename T>
void vector<T>::pop_back() {
  size_ -= 1;
}

template <typename T>
void vector<T>::swap(vector<T> &other) {
  std::swap(array_, other.array_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
void vector<T>::realloc_array(size_type new_capacity) {
  if (new_capacity > max_size()) {
    throw std::length_error("trying to allocate as much as possible");
  }
  delete[] array_;
  if (new_capacity != 0) {
    array_ = new value_type[new_capacity]();
  } else {
    array_ = nullptr;
  }
  capacity_ = new_capacity;
}

template <typename T>
void vector<T>::realloc_and_copy(size_type new_capacity) {
  if (new_capacity > max_size()) {
    throw std::length_error("trying to allocate as much as possible");
  }
  size_type old_size = size_;
  vector<value_type> new_vector(new_capacity);
  std::copy(begin(), end(), new_vector.begin());
  *this = std::move(new_vector);
  size_ = old_size;
}

}  // namespace s21
