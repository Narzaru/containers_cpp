#include "s21_vector.h"

namespace s21 {

template<typename T>
vector<T>::vector() : vector(0) {}

template<typename T>
vector<T>::vector(vector<T>::size_type capacity)
    : array_(nullptr),
      size_(0),
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
  vector<T>::clear();
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
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.clear();
}

template<typename T>
void vector<T>::clear() {
  delete[] array_;
  size_ = 0;
  capacity_ = 0;
}

template<typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template<typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template<typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

// TODO(bgreydon) use copy_array instead for
template<typename T>
void vector<T>::copy_array(const vector<T> &from,
                           vector<T> *to,
                           size_type size) {
  for (size_type i = 0; i < size; ++i) {
    to->array_[i] = from.array_[i];
  }
}

template<typename T>
void vector<T>::copy_array(vector<T>::const_iterator from,
                           vector<T>::iterator to,
                           vector<T>::size_type size) {
  for (vector<T>::size_type i = 0; i < size; ++i) {
    to[i] = from[i];
  }
}

template<typename T>
void vector<T>::realloc_array(size_type capacity) {
  capacity_ = capacity;
  delete[] array_;
  if (capacity != 0) {
    array_ = new T[capacity]();
  } else {
    array_ = nullptr;
  }
}

template<typename T>
void vector<T>::realloc_and_copy(vector<T>::size_type capacity) {
  vector<T> new_vector(capacity);
  copy_array(*this, &new_vector, size_ > capacity ? capacity : size_);
  *this = std::move(new_vector);
}

template<typename T>
bool vector<T>::empty() const {
  return size_ == 0;
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
void vector<T>::reserve(vector<T>::size_type new_capacity) {
  if (new_capacity > max_size()) {
    throw std::length_error("trying to allocate as much as possible");
  }
  if (new_capacity > capacity_) {
    realloc_and_copy(new_capacity);
  }
}

template<typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    realloc_and_copy(size_);
  }
}


}  // namespace s21
