// #include "s21_list.h"
#include <cstddef>
#include <ostream>
#include <initializer_list>
#include <iostream>
#include <climits>
#include <type_traits>
#include <utility>

#include "s21_list.h"

namespace s21 {

    template <typename T>
    void list<T>::listNode::free_memory() {
        pNext = nullptr;
        pPrev = nullptr;
        // data тоже надо очистить но я не знаю как потому что если массив то delete []  а если переменная то просто 0
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
    list<T>::list(): list(0) {}

    template <typename T>
    list<T>::list(size_t size) {
      size_ = 0;
      head_ = back_ = nullptr;
      for (size_type i = 0; i < size; ++i) {
        push_back(T());
      }
    }

    template <typename T>
    list<T>::list(std::initializer_list<T> const& items) : list() {
        for (const auto &data:items) {
          push_back(data);
        }
    }

    template <typename T>
    list<T>::list(const list &l) : size_(0) {
      for (list<T>::ListConstIterator at(l); at.itr; ++at) {
        push_back(*at);
      }
    }

    template <typename T>
    list<T>::list(list &&l) : list() {
      head_ = l.head_;
      back_ = l.back_;
      size_ = l.size_;
      l.head_ = nullptr;
      l.back_ = nullptr;
      l.size_ = 0;
    }

    template <typename T>
    void list<T>::push_back (T data) {
      if (size_ == 0) {
        head_ = new node(data, nullptr, nullptr);
        back_ = head_;
      } else {
        back_->pNext = new node(data, nullptr, back_);
        back_ = back_->pNext;
      }
      ++size_;
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
    size_t list<T>::max_size(){
        return LLONG_MAX / sizeof(node) -1;
    }

    template <typename T>
    void list<T>::clear() {
      while(!empty()) {
        pop_back();
      }
    }


    template <typename T>
    void list<T>::free_data_list() {
        if (!empty()){
            node *p = head_;
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
    void list<T>::pop_back(){
        if (size_ > 1) {
          back_ = back_->pPrev;
          delete back_->pNext;
          back_->pNext = nullptr;
        } else {
          delete head_;
          head_ = nullptr;
        }
        --size_;
    }

    template <typename T>
    void list<T>::push_front (T data) {
      if (size_ == 0) {
        head_ = new node(data, nullptr, nullptr);
        back_ = head_;
      } else {
        head_->pPrev = new node(data, head_, nullptr);
        head_ = head_->pPrev;
      }
      ++size_;
    }

    template <typename T>
    void list<T>::pop_front() {
        if (size_ > 1) {
          head_ = head_->pNext;
          delete head_->pPrev;
          head_->pPrev = nullptr;
        } else {
          delete head_;
          head_ = nullptr;
        }
        --size_;
    }

    template <typename T>
    void list<T>::print_cont(){
        node *current = head_;
        int count = size_;
        while (count != 0)
        {
            std::cout << current->data << std::endl;
            --count;
            current = current->pNext;
        }

    }

    template <typename T>
    list<T>& list<T>::operator=(list& other) {
        clear();
        list<T>::ListIterator ptr(other);
        while (ptr.itr) {
            push_back(*ptr);
            ptr++;
        }
        return *this;
    }

    template <typename T>
    T& list<T>::front() const{
        list<T>::ListIterator tmp(*this);
        return *tmp;
    }

    template <typename T>
    T& list<T>::back() const{
        list<T>::ListIterator ptr(*this);
        ptr.itr = ptr.end;
        return *ptr;
    }

    template <typename T>
    void list<T>::reverse() {
        list<T> newList;
        list<T>::ListIterator at = begin();
        for (size_type i = 0; i < size_; ++i, at++) {
          newList.push_front(at.itr->data);
        }
        *this = newList;
    }

// bgreydon
// на сегодня я уже всё, остальные ошибки исправил, из тестов это последняя
// функция
    template <typename T>
    void list<T>::unique() {
        list<T>::ListIterator ptr = this->begin();
        auto c = *ptr;
        ptr++;
        while (ptr.itr) {
            if ( c == *ptr) {
                ptr.itr->pPrev->pNext = ptr.itr->pNext;
                if (ptr.itr->pNext != nullptr) {
                    ptr.itr->pNext->pPrev = ptr.itr->pPrev;
                }
                ptr++;
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

        for (size_t i = 0 ; i < size_ - 1; ++i) {
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
    void list<T>::iterator::swap_elements(typename list<T>::ListIterator other) {
        T tmp = other.itr->data;
        other.itr->data = itr->data;
        itr->data = tmp;
    }

    template <typename T>
    void list<T>::merge(list& other) {
        list<T>::iterator first = this->end();
        list<T>::iterator second = other.begin();
        first.end->pNext = other.head_;
        other.head_->pPrev = first.itr;
        size_+= other.size_;
        last_node();
    }

    template <typename T>
    void list<T>::swap(list& other) {
      std::swap(head_, other.head_);
      std::swap(back_, other.back_);
      std::swap(size_, other.size_);
    }

    template <typename T>
    void list<T>::erase(typename list<T>::ListIterator pos) {
      if (pos.itr->pPrev != nullptr) {
        pos.itr->pPrev->pNext = pos.itr->pNext;
      } else {
        head_ = pos.itr->pNext;
      }

      if (pos.itr->pNext != nullptr) {
        pos.itr->pNext->pPrev = pos.itr->pPrev;
      } else {
        back_ = pos.itr->pPrev;
      }
      --size_;
      delete pos.itr;
    }

    template <typename T>
    void list<T>::splice(const_iterator pos, list& other) {
        iterator tmp = other.begin();
        pos.itr->pNext->pPrev = tmp.end;
        tmp.end->pNext = pos.itr->pNext;
        pos.itr->pNext = tmp.itr;
        tmp.itr->pPrev = pos.itr;
        size_ +=other.size_;
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
    T& list<T>::ListIterator::operator* () const {
        if (itr == nullptr) {
            // бросить исключение
        }
        return itr->data;
    }

    template <typename T>
    typename list<T>::ListIterator list<T>::ListIterator::operator++ () {
        if (itr == nullptr) {
            // бросить исключение
        }
        itr = itr->pNext;
        return *this;
    }

    template <typename T>
    typename list<T>::ListIterator list<T>::ListIterator::operator++ (int) {
        if (itr == nullptr) {
            // бросить исключение
        }
        iterator ptr = *this;
        itr = itr->pNext;
        return ptr;
    }

    template <typename T>
    typename list<T>::ListIterator list<T>::ListIterator::operator-- () {
        if (itr == nullptr) {
            // бросить исключение
        }
        itr = itr->pPrev;
        return *this;
    }

    template <typename T>
    typename list<T>::ListIterator list<T>::ListIterator::operator-- (int) {
        if (itr == nullptr) {
            // бросить исключение
        }
        iterator ptr = *this;
        itr = itr->pPrev;
        return ptr;
    }

    template <typename T>
    bool list<T>::ListIterator:: operator== (const ListIterator& other) {
        return itr == other.itr;
    }

    template <typename T>
    bool list<T>::ListIterator:: operator!= (const ListIterator& other) {
        return itr != other.itr;
    }

    template <typename T>
    typename list<T>::iterator  list<T>::begin() {
        return ListIterator(*this);
    }

    template <typename T>
    typename list<T>::iterator  list<T>::end() {
        ListIterator tmp(*this);
        while (tmp.itr->pNext != nullptr) {
            tmp++;
        }
        return tmp;
    }

    template <typename T>
    typename list<T>::ListIterator list<T>::insert (ListIterator pos, const T& value) {
        node* element = new node(value, pos.itr, pos.itr->pPrev);
        pos.itr->pPrev = element;
        if (element->pPrev != nullptr) {
          element->pPrev->pNext = element;
        } else {
          head_ = element;
        }
        --pos;
        ++size_;
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
    typename list<T>::ListConstIterator list<T>::ListConstIterator::operator++ () {
        if (itr == nullptr) {
            // бросить исключение
        }
        itr = itr->pNext;
        return *this;
    }

    template <typename T>
    typename list<T>::ListConstIterator list<T>::ListConstIterator::operator++ (int) {
        if (itr == nullptr) {
            // бросить исключение
        }
        const_iterator ptr = *this;
        itr = itr->pNext;
        return ptr;
    }

    template <typename T>
    typename list<T>::ListConstIterator list<T>::ListConstIterator::operator-- () {
        if (itr == nullptr) {
            // бросить исключение
        }
        itr = itr->pPrev;
        return *this;
    }

    template <typename T>
    typename list<T>::ListConstIterator list<T>::ListConstIterator::operator-- (int) {
        if (itr == nullptr) {
            // бросить исключение
        }
        const_iterator ptr = *this;
        itr = itr->pPrev;
        return ptr;
    }

    template <typename T>
    bool list<T>::ListConstIterator:: operator== (const ListConstIterator& other) {
        return itr == other.itr;
    }

    template <typename T>
    bool list<T>::ListConstIterator:: operator!= (const ListConstIterator& other) {
        return itr != other.itr;
    }

    template <typename T>
    typename list<T>::const_iterator  list<T>::cbegin() const{
        return ListConstIterator(*this);
    }

    template <typename T>
    typename list<T>::const_iterator  list<T>::cend() const{
        ListConstIterator tmp(*this);
        while (tmp.itr != tmp.end) {
            tmp++;
        }
        return ListConstIterator(tmp);
    }

} // namespace s21
