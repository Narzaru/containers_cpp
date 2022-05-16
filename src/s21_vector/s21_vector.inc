#include "s21_vector.h"

namespace s21 {

template<typename T>
vector<T>::vector() : vector(0) {}

template<typename T>
vector<T>::vector(vector<T>::size_type capacity)
    : array_(nullptr),
      size_(capacity),
      capacity_(capacity) {
  realloc_array(capacity);
}

template<typename T>
vector<T>::vector(std::initializer_list<T> const &list)
    : vector(list.size()) {
  size_ = list.size();
  for (size_type i = 0; i < list.size(); ++i) {
    array_[i] = list.begin()[i];
  }
}

template<typename T>
vector<T>::vector(const vector<T> &other)
    : vector(other.capacity_) {
  size_ = other.size_;
  copy_array(this, other, other.size_);
}

template<typename T>
vector<T>::vector(vector<T> &&other) noexcept
    : array_(other.array_),
      size_(other.size_),
      capacity_(other.capacity_) {
  other.array_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template<typename T>
vector<T>::~vector() {
  vector < T > ::clear();
}

template<typename T>
vector<T> &vector<T>::operator=(const vector<T> &other) {
  if (capacity_ != other.capacity_) {
    capacity_ = other.capacity_;
    realloc_array(*this, capacity_);
  }
  copy_array(other, this, other.size_);
  size_ = other.size_;
}

template<typename T>
vector<T> &vector<T>::operator=(vector &&other) noexcept {
  clear();
  array_ = other.array_;
  other.array_ = nullptr;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.clear();
  return *this;
}

template<typename T>
typename vector<T>::reference vector<T>::at(size_type position) {
  return const_cast<vector<T>::reference>(const_cast<const vector<T> *>(this)->at(
      position));
}

template<typename T>
typename vector<T>::const_reference vector<T>::at(size_type position) const {
  if (position >= size_) {
    throw std::out_of_range("index is out of range");
  }
  if (capacity_ == 0) {
    throw std::length_error("vector is empty");
  }
  return array_[position];
}

template<typename T>
typename vector<T>::reference vector<T>::operator[](size_type position) {
  return at(position);
}

template<typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type position) const {
  return at(position);
}

template<typename T>
typename vector<T>::reference vector<T>::front() {
  return *array_;
}

template<typename T>
typename vector<T>::const_reference vector<T>::front() const {
  return const_cast<vector<T>::const_reference>(front());
}

template<typename T>
typename vector<T>::reference vector<T>::back() {
  return *(array_ + size_);
}

template<typename T>
typename vector<T>::const_reference vector<T>::back() const {
  return const_cast<vector<T>::const_reference>(back());
}

template<typename T>
typename vector<T>::iterator vector<T>::data() {
  return &front();
}

template<typename T>
typename vector<T>::const_iterator vector<T>::data() const {
  return &front();
}

template<typename T>
typename vector<T>::iterator vector<T>::begin() {
  return &front();
}

template<typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return &front();
}

template<typename T>
typename vector<T>::iterator vector<T>::end() {
  return &back();
}

template<typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return &back();
}

template<typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template<typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template<typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template<typename T>
void vector<T>::reserve(vector<T>::size_type new_capacity) {
  if (new_capacity > max_size()) {
    throw std::length_error("trying to allocate as much as possible");
  }
  if (new_capacity > capacity_) {
    realloc_and_copy(new_capacity);
  }
}

template<typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template<typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    realloc_and_copy(size_);
  }
}

template<typename T>
void vector<T>::clear() {
  delete[] array_;
  size_ = 0;
  capacity_ = 0;
}

template<typename T>
T *vector<T>::insert(T *pos, const T &value) {
  std::size_t insert_position = (pos - array_) / sizeof(T);
  if (insert_position > size_) {
    throw std::out_of_range("insert position is out of range");
  }
  if (insert_position > max_size()) {
    throw std::length_error("trying to allocate as much as possible");
  }
  if (size_ + 1 > capacity_) {
    realloc_and_copy(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  for (std::size_t i = size_; i != insert_position; --i) {
    array_[i] = array_[i - 1];
  }
  array_[insert_position] = value;
  size_ += 1;
  return pos;
}

template<typename T>
void vector<T>::erase(iterator pos) {

}

// TODO(bgreydon) use copy_array instead for
template<typename T>
void vector<T>::copy_array(const vector<T> &source,
                           vector<T> *destination,
                           size_type size) {
  for (size_type i = 0; i < size; ++i) {
    destination->array_[i] = source.array_[i];
  }
}

template<typename T>
void vector<T>::copy_array(vector<T>::const_iterator source,
                           vector<T>::iterator destination,
                           vector<T>::size_type size) {
  for (std::size_t i = 0; i < size; ++i) {
    destination[i] = source[i];
  }
}

template<typename T>
void vector<T>::realloc_array(size_type new_capacity) {
  if (new_capacity > max_size()) {
    throw std::length_error("trying to allocate as much as possible");
  }
  capacity_ = new_capacity;
  delete[] array_;
  if (new_capacity != 0) {
    array_ = new T[new_capacity]();
  } else {
    array_ = nullptr;
  }
}

template<typename T>
void vector<T>::realloc_and_copy(vector<T>::size_type new_capacity) {
  if (new_capacity > max_size()) {
    throw std::length_error("trying to allocate as much as possible");
  }
  std::size_t old_size = size_;
  vector<T> new_vector(new_capacity);
  copy_array(*this, &new_vector, size_);
  *this = std::move(new_vector);
  size_ = old_size;
}

}  // namespace s21
