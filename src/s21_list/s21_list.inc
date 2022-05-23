// #include "s21_list.h"
#include <climits>
#include <initializer_list>
#include <iostream>
#include <ostream>

namespace s21 {

template <typename T>
list<T>::list() : size_(0), head_(nullptr), back_(nullptr) {}

template <typename T>
list<T>::list(size_t n) : size_(0) {
  // head_ = new node;
  // head_->pNext = nullptr;
  // head_->pPrev = nullptr;
  // size_ = 0;
  for (size_t i = 0; i < n; i++) push_back(0);
}

template <typename T>
list<T>::list(std::initializer_list<T> const& items) : size_(0) {
  // head_ = new node();
  // head_-> pNext = nullptr;
  // head_-> pPrev = nullptr;
  for (const auto& data : items) push_back(data);
}

template <typename T>
list<T>::list(list&& l) : size_(0) {
  if (&l != this) {
    head_ = l.head_;
    l.head_ = new node;
    l.head_->pNext = l.head_;
    l.head_->pPrev = l.head_;
    size_ = l.size_;
    l.size_ = 0;
  } else {
    head_ = new node;
    head_->pNext = nullptr;
    head_->pPrev = nullptr;
  }
}

template <typename T>
list<T>::list(const list& l) : size_(0) {
  // head_ = new node();
  list<T>::ListIterator ptr(l);
  while (ptr.itr) {
    push_back(*ptr);
    ptr++;
  }
}

template <typename T>
list<T>& list<T>::operator=(const list& other) {
  if (size_ != 0) {
    this->clear();
  }
  list<T>::ListIterator ptr(other);
  while (ptr.itr) {
    push_back(*ptr);
    ptr++;
  }
  return *this;
}

template <typename T>
void list<T>::listNode::free_memory() {
  pNext = nullptr;
  pPrev = nullptr;
  // data = 0;
  // data тоже надо очистить но я не знаю как потому что если массив то delete
  // []  а если переменная то просто 0
}

template <typename T>
void list<T>::last_node() {
  node* p = head_;
  // head_->pNext = nullptr;
  // head_->pPrev = nullptr;
  while (p->pNext != nullptr) {
    p = p->pNext;
  }
  back_ = p;
}

template <typename T>
void list<T>::push_back(T data) {
  if (size_ == 0) {
    // head_->pNext = nullptr;
    // head_->pPrev = nullptr;
    this->head_ = new node;
    head_->data = data;
    ++size_;
  } else {
    node* p = head_;
    while (p->pNext != nullptr) {
      p = p->pNext;
    }
    node* tmp = new node;
    tmp->pPrev = p;
    tmp->pNext = nullptr;
    tmp->data = data;
    p->pNext = tmp;
    ++size_;
  }
  last_node();
}

template <typename T>
bool list<T>::empty() {
  return size() == 0;
}

template <typename T>
size_t list<T>::size() {
  return size_;
}

template <typename T>
size_t list<T>::max_size() {
  return LLONG_MAX / sizeof(node) - 1;
}

template <typename T>
void list<T>::clear() {
  if (empty() == false) {
    node* p = head_;
    while (p->pNext != nullptr) {
      p = p->pNext;
    }
    while (p->pPrev != nullptr) {
      p = p->pPrev;
      delete p->pNext;
      --size_;
    }
    delete p;
    --size_;
  } else {
    delete head_;
  }
}

template <typename T>
void list<T>::free_data_list() {
  if (empty() == 0) {
    node* p = head_;
    while (p->pNext != nullptr) {
      p = p->pNext;
    }
    while (p->pPrev != nullptr) {
      p = p->pPrev;
      delete p->pNext;
      --size_;
    }
    head_->pNext = nullptr;
    head_->pPrev = nullptr;
    --size_;
  }
}

template <typename T>
void list<T>::pop_back() {
  list<T>::ListIterator ptr(*this);
  ptr.end->pPrev->pNext = nullptr;
  delete ptr.end;
  // ptr.end->free_memory();
  size_--;
  last_node();
}

template <typename T>
void list<T>::push_front(T data) {
  if (size_ == 0) {
    head_ = new node;
    head_->pNext = nullptr;
    head_->pPrev = nullptr;
    head_->data = data;
    ++size_;
  } else {
    // node *second = new node;
    // second->data = head_->data;
    // second->pNext = head_->pNext;
    // second->pPrev = head_;

    // head_->data = data;
    // head_->pPrev = nullptr;
    // head_->pNext = second;
    // size_++;
    node* first = new node;
    first->data = data;
    first->pPrev = nullptr;
    first->pNext = head_;
    head_->pPrev = first;
    head_ = first;
    ++size_;
  }
}

template <typename T>
void list<T>::pop_front() {
  if (size_ > 1) {
    head_ = head_->pNext;
    delete head_->pPrev;
    // head_->pPrev->free_memory();
    head_->pPrev = nullptr;
  } else {
    // list<T>::ListIterator ptr(*this);
    // delete ptr.first;
    // head_->free_memory();
    // delete head_;
    delete head_->pPrev;
  }
  size_--;
}

template <typename T>
void list<T>::print_cont() {
  node* current = head_;
  int count = size_;
  while (count != 0) {
    std::cout << current->data << std::endl;
    --count;
    current = current->pNext;
  }
}

template <typename T>
T& list<T>::front() const {
  list<T>::ListIterator tmp(*this);
  return *tmp;
}

template <typename T>
T& list<T>::back() const {
  list<T>::ListIterator ptr(*this);
  ptr.itr = ptr.end;
  return *ptr;
}

template <typename T>
void list<T>::reverse() {
  list<T> ptr;
  list<T>::ListIterator tmp = this->begin();
  for (; ptr.size_ < size_;) {
    ptr.push_front(*tmp);
    tmp++;
  }
  *this = ptr;
}

template <typename T>
void list<T>::unique() {
  list<T>::ListIterator ptr = this->begin();
  auto c = *ptr;
  ptr++;
  while (ptr.itr) {
    if (c == *ptr) {
      ptr.itr->pPrev->pNext = ptr.itr->pNext;
      if (ptr.itr->pNext != nullptr) {
        ptr.itr->pNext->pPrev = ptr.itr->pPrev;
      }
      node* tmp = ptr.itr;
      ptr++;
      delete tmp;
      size_--;
    } else {
      c = *ptr;
      ptr++;
    }
  }
}

template <typename T>
void list<T>::sort() {
  list<T>::ListIterator ptr_i = begin();

  for (size_t i = 0; i < size_ - 1; ++i) {
    bool flag = true;
    for (size_t j = 0; j < size_ - i - 1; ++j, ++ptr_i) {
      if (ptr_i.itr->data > ptr_i.itr->pNext->data) {
        flag = false;
        std::swap(ptr_i.itr->data, ptr_i.itr->pNext->data);
      }
    }
    ptr_i = begin();
    if (flag) {
      break;
    }
  }
}

template <typename T>
void list<T>::iterator::swap_elements(typename list<T>::ListIterator pos) {
  T tmp = pos.itr->data;
  pos.itr->data = itr->data;
  itr->data = tmp;
}

template <typename T>
void list<T>::merge(list& other) {
  list<T>::iterator first = this->end();
  list<T>::iterator second = other.begin();
  first.end->pNext = other.head_;
  other.head_->pPrev = first.itr;
  size_ += other.size_;
  last_node();
}

template <typename T>
void list<T>::swap(list& other) {
  node* tmp;
  tmp = other.head_;
  other.head_ = head_;
  head_ = tmp;
  int tmp_size = other.size_;
  other.size_ = size_;
  size_ = tmp_size;
}

template <typename T>
void list<T>::erase(typename list<T>::ListIterator pos) {
  if (pos.itr == pos.end) {
    // pos--;
    // pos.itr->pNext = nullptr;
    // size_--;
    pop_back();
  } else if (pos.itr == pos.first) {
    pop_front();
  } else {
    pos.itr->pPrev->pNext = pos.itr->pNext;
    pos.itr->pNext->pPrev = pos.itr->pPrev;
    // pos.itr->pPrev->free_memory();
    delete pos.itr;
    size_--;
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list& other) {
  iterator tmp = other.begin();
  pos.itr->pNext->pPrev = tmp.end;
  tmp.end->pNext = pos.itr->pNext;
  pos.itr->pNext = tmp.itr;
  tmp.itr->pPrev = pos.itr;
  size_ += other.size_;
  other.free_data_list();
}

// ITERATOR

template <typename T>
void list<T>::ListIterator::free_iterator() {
  first = nullptr;
  end = nullptr;
  itr = nullptr;
}

template <typename T>
T& list<T>::ListIterator::operator*() const {
  if (itr == nullptr) {
    // бросить исключение
  }
  return itr->data;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator++() {
  if (itr == nullptr) {
    // бросить исключение
  }
  itr = itr->pNext;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator++(int) {
  if (itr == nullptr) {
    // бросить исключение
  }
  iterator ptr = *this;
  itr = itr->pNext;
  return ptr;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator--() {
  if (itr == nullptr) {
    // бросить исключение
  }
  itr = itr->pPrev;
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator--(int) {
  if (itr == nullptr) {
    // бросить исключение
  }
  iterator ptr = *this;
  itr = itr->pPrev;
  return ptr;
}

template <typename T>
bool list<T>::ListIterator::operator==(const ListIterator& other) {
  return itr == other.itr;
}

template <typename T>
bool list<T>::ListIterator::operator!=(const ListIterator& other) {
  return itr != other.itr;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return ListIterator(*this);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  ListIterator tmp(*this);
  while (tmp.itr->pNext != nullptr) {
    tmp++;
  }
  return tmp;
}

template <typename T>
typename list<T>::ListIterator list<T>::insert(ListIterator pos,
                                               const T& value) {
  node* element = new node;
  element->data = pos.itr->data;
  pos.itr->data = value;
  element->pPrev = pos.itr;
  element->pNext = pos.itr->pNext;
  pos.itr->pNext->pPrev = element;
  pos.itr->pNext = element;
  pos++;
  size_++;
  return pos;
}

// CONST ITERATOR

template <typename T>
void list<T>::ListConstIterator::free_iterator() {
  first = nullptr;
  end = nullptr;
  itr = nullptr;
}

template <typename T>
T& list<T>::ListConstIterator::operator*() const {
  if (itr == nullptr) {
    // бросить исключение
  }
  return itr->data;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator++() {
  if (itr == nullptr) {
    // бросить исключение
  }
  itr = itr->pNext;
  return *this;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator++(
    int) {
  if (itr == nullptr) {
    // бросить исключение
  }
  const_iterator ptr = *this;
  itr = itr->pNext;
  return ptr;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator--() {
  if (itr == nullptr) {
    // бросить исключение
  }
  itr = itr->pPrev;
  return *this;
}

template <typename T>
typename list<T>::ListConstIterator list<T>::ListConstIterator::operator--(
    int) {
  if (itr == nullptr) {
    // бросить исключение
  }
  const_iterator ptr = *this;
  itr = itr->pPrev;
  return ptr;
}

template <typename T>
bool list<T>::ListConstIterator::operator==(const ListConstIterator& other) {
  return itr == other.itr;
}

template <typename T>
bool list<T>::ListConstIterator::operator!=(const ListConstIterator& other) {
  return itr != other.itr;
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return ListConstIterator(*this);
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const {
  ListConstIterator tmp(*this);
  while (tmp.itr != tmp.end) {
    tmp++;
  }
  return ListConstIterator(tmp);
}

}  // namespace s21
