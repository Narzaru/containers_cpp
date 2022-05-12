// TODO(bgreydon) remove done and tested marks
namespace s21 {

// !done
// !
template<typename T>
vector<T>::vector() : vector<T>::vector(0) {}

// !done
// !
template<typename T>
vector<T>::vector(size_type size)
  : array_(new T[size]()),
    size_(size),
    capacity_(size) {}

template<typename T>
vector<T>::vector(std::initializer_list<T> const &list) : vector<T>::vector(list.size()) {}

template<typename T>
vector<T>::vector(const vector<T> &other) : vector<T>::vector(other.capacity_) {

}

// !done
// !
template<typename T>
vector<T>::vector(vector<T> &&other)
  : array_(other.array_),
    size_(other.size_),
    capacity_(other.capacity_) {
  other.array_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

// !done
// !
template<typename T>
vector<T>::~vector() {
  vector<T>::clear();
}

// !done
// !
template<typename T>
void vector<T>::clear() {
  delete[] array_;
  size_ = 0;
  capacity_ = 0;
}

}  // namespace s21
