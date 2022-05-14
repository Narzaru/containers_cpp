// TODO(bgreydon) remove marks
// !<done or not> done/..
// !<tested or not> tested/..
// !<temp> ?
namespace s21 {

// !done
// !..
template<typename T>
vector<T>::vector() : vector(0) {}

// !done
// !..
template<typename T>
vector<T>::vector(size_type capacity)
    : array_(nullptr),
      size_(0),
      capacity_(capacity) {
  realloc_array(capacity);
}

// !done
// !..
template<typename T>
vector<T>::vector(std::initializer_list<T> const &list)
    : vector(list.size()) {
  for (size_type i = 0; i < list.size(); ++i) {
    array_[i] = list.begin()[i];
  }
}

// !done
// !..
template<typename T>
vector<T>::vector(const vector<T> &other)
    : vector(other.capacity_) {
  size_ = other.size_;
  copy_array(this, other, other.size_);
}

// !done
// !..
template<typename T>
vector<T>::vector(vector<T> &&other) noexcept
    : array_(other.array_),
      size_(other.size_),
      capacity_(other.capacity_) {
  other.array_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

// !done
// !..
template<typename T>
vector<T>::~vector() {
  vector<T>::clear();
}

// !done
// !..
template<typename T>
vector<T>& vector<T>::operator=(const vector<T> &other) {
  if (capacity_ != other.capacity_) {
    capacity_ = other.capacity_;
    realloc_array(*this, capacity_);
  }
  copy_array(other, this, other.size_);
  size_ = other.size_;
}

// !done
// !..
template<typename T>
vector<T>& vector<T>::operator=(vector &&other) {
  clear();
  array_ = other.array_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.clear();
}

// !done
// !..
template<typename T>
void vector<T>::clear() {
  delete[] array_;
  size_ = 0;
  capacity_ = 0;
}

// !done
// !..
template<typename T>
void vector<T>::copy_array(const vector<T> &from, vector<T> *to, size_type size) {
  for (size_type i = 0; i < size; ++i) {
    to->array_[i] = from.array_[i];
  }
}

// !done
// !..
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

}  // namespace s21
