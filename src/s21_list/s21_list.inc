// #include "s21_list.h"
#include <ostream>
#include <initializer_list>
#include <iostream>
#include <climits>

namespace s21 {

    template <typename T>
    void list<T>::listNode::free_memory() {
        pNext = nullptr;
        pPrev = nullptr;
    }

    template <typename T>
    void list<T>::last_node() {
        node* p = head_;
        while (p->pNext != nullptr) {
                p = p->pNext;
        }
        back_ = p;
    }

    template <typename T>
    list<T>::list(): size_(0), head_(nullptr), back_(nullptr) {}

    template <typename T>
    list<T>::list(size_t n) : size_(0) {
        for (size_t i = 0; i < n; i++) {
            push_back(0);
        }
    }

    template <typename T>
    list<T>::list(std::initializer_list<T> const& items) : size_(0) {
        for (const auto &data:items) {
            push_back(data);
        }
    }

    template <typename T>
    list<T>::list(const list &l) : size_(0) {
        list<T>::ListIterator ptr(l);
        while (ptr.itr) {
            push_back(*ptr);
            ptr++;
        }
    }

    template <typename T>
    list<T>::list(list &&l) : size_(0) {
        if (&l != this) {
            head_ = l.head_;
            size_ = l.size_;
            l.head_ = nullptr;
            l.back_ = back_;
            l.size_ = 0;
        } else {
            head_ = new node;
            head_->pNext = nullptr;
            head_->pPrev = nullptr;
        }
    }

    template <typename T>
    void list<T>::push_back (T data) {
        if (size_ == 0) {
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
    size_t list<T>::max_size(){
        return LLONG_MAX / sizeof(node) -1;
    }

    template <typename T>
    void list<T>::clear() {
        if (empty() == false) {
            node *p = head_;
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
        }
    }

    template <typename T>
    void list<T>::pop_back() {
        list<T>::ListIterator ptr(*this);
        ptr.end->pPrev->pNext = nullptr;
        delete ptr.end;
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
            node *first = new node;
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
            head_->pPrev = nullptr;
        } else if (size_ == 1){
            delete head_;
        }
        size_--;
    }

    template <class T>
    list<T> &list<T>::operator=(const list &l) {
        if (size_ != 0) {
            this->clear();
        }
        list<T>::ListIterator ptr(l);
        while (ptr.itr) {
            push_back(*ptr);
            ptr++;
        }
        return *this;
    }

    template <class T>
    list<T> &list<T>::operator=(list &&l) {
        *this = l;
        l.clear();
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
        list<T> ptr(*this);
        list<T>::ListIterator tmp = ptr.begin();
        this->clear();
        for (; this->size_ < ptr.size_ ;) {
            this->push_front(*tmp);
            tmp++;
        }
    }

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
                node *tmp = ptr.itr;
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
    void list<T>::iterator::swap_elements(typename list<T>::ListIterator l) {
        T tmp = l.itr->data;
        l.itr->data = itr->data;
        itr->data = tmp;
    }

    template <typename T>
    void list<T>::merge(const list& other) {
        list<T>::iterator first = this->end();
        list<T>::iterator second = other.begin();
        first.end->pNext = other.head_;
        other.head_->pPrev = first.itr;
        size_+= other.size_;
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
            pop_back();
        } else if (pos.itr == pos.first) {
            pop_front();
        } else {
            pos.itr->pPrev->pNext = pos.itr->pNext;
            pos.itr->pNext->pPrev = pos.itr->pPrev;
            delete pos.itr;
            size_--;
        }
    }

    template <typename T>
    void list<T>::splice(const_iterator pos, const list& l) {
        iterator tmp = l.begin();
        pos.itr->pNext->pPrev = tmp.end;
        tmp.end->pNext = pos.itr->pNext;
        pos.itr->pNext = tmp.itr;
        tmp.itr->pPrev = pos.itr;
        size_ +=l.size_;
        l.clear();
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
    bool list<T>::ListIterator::operator== (const ListIterator& l) {
        return itr == l.itr;
    }

    template <typename T>
    bool list<T>::ListIterator::operator!= (const ListIterator& l) {
        return itr != l.itr;
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
    typename list<T>::iterator list<T>::insert (ListIterator pos, const T& value) {
        if (pos.itr != pos.end) {
            node* element = new node;
            element->data = pos.itr->data;
            pos.itr->data = value;
            element->pPrev = pos.itr;
            element->pNext = pos.itr->pNext;
            pos.itr->pNext->pPrev = element;
            pos.itr->pNext = element;
            size_++;
        } else if (pos.itr == pos.first) {
            push_front(value);
        } else {
            push_back(value);
        }
        pos++;
        return pos;
    }

    /**
    * @brief перегрузка для emplace
    * 
    * @tparam T 
    * @param pos 
    * @param other 
    * @return list<T>::iterator 
    */
    template <typename T>
    typename list<T>::iterator list<T>::insert (ListConstIterator pos, list<T>&& other) {
        iterator result = begin();
        iterator ptr = other.end();
        for (; result.itr != pos.itr; ++result) {}        
        for (; ptr.itr != nullptr ;) {
            insert(result, *ptr);
            ptr--;
        }
        return result;
    }

    template <typename T>
    template <typename... Args>
    void list<T>::emplace(ListConstIterator pos, Args&&... args) {
        std::initializer_list<T> lst = {args...};
        list<T> tmp(lst);
        if (pos.itr == pos.end) {
            tmp.reverse();
        }
        insert(pos, std::move(tmp));
    }

    template <typename T>
    template <typename... Args>
    void list<T>::emplace_back(Args&&... args) {
        ListConstIterator pos = this->cend();
        emplace(pos, args...);
    }

    template <typename T>
    template <typename... Args>
    void list<T>::emplace_front(Args&&... args) {
        ListConstIterator pos = this->cbegin();
        emplace(pos, args...);
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
    bool list<T>::ListConstIterator:: operator== (const ListConstIterator& l) {
        return itr == l.itr;
    }

    template <typename T>
    bool list<T>::ListConstIterator:: operator!= (const ListConstIterator& l) {
        return itr != l.itr;
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
