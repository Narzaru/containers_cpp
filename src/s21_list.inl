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
        data = 0;
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
    list<T>::list(): size_(0) {
        head_ = new node();
        head_-> pNext = nullptr;
        head_-> pPrev = nullptr;
        last_node();
    }

    template <typename T>
    list<T>::list(size_t n) {
        head_ = new node;
        head_->pNext = head_;
        head_->pPrev = nullptr;
        size_ = 0;
        for (size_t i = 0; i < n; i++)
            push_back(0);
        
    }

    template <typename T>
    list<T>::list(std::initializer_list<T> const& items) : size_(0) {
        head_ = new node();
        head_-> pNext = nullptr;
        head_-> pPrev = nullptr;
        for (const auto data:items)
            push_back(data);
    }

    template <typename T>
    list<T>::list(const list &l) : size_(0) {
        head_ = new node();
        list<T>::ListIterator ptr(l);
        while (ptr.itr) {
            push_back(*ptr);
            ptr++;
        } 
    }

    template <typename T>
    list<T>::list(list &&l) : size_(0) {
        list<T> ptr(l);
        l.clear();
        *this = ptr;
    }

    template <typename T>
    void list<T>::push_back (T data) {
        if (size_ == 0) {
            head_->pNext = nullptr;
            head_->pPrev = nullptr;
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
    bool list<T>::emply() {
        return size() == 0;
    }

    template <typename T>
    size_t list<T>::size() {
        return size_;
    }

    template <typename T>
    size_t list<T>::max_size(){
        return LLONG_MAX / sizeof(node);
    }

    template <typename T>
    void list<T>::clear() {        // нужно переделать на удаление с конца (указатель на конец) а не проходить через весь лист
        if (emply() == 0){
            node *p = head_;
            int count = 0;
            while (p->pNext != nullptr) {
                p = p->pNext;
                count++;
            }
            while (p->pPrev != nullptr) {
                node *tmp = p; 
                p = p->pPrev;
                tmp->free_memory();
                --size_;
            }
            p->free_memory();   // очищаяет послдний элемент
            --size_;
        }
    }

    template <typename T>
    void list<T>::pop_back(){    
        node *p = head_;    
        while (p->pNext->pNext != nullptr) {
            p = p->pNext;
        }
        node *tmp = p->pNext;
        p->pNext = nullptr;
        size_--;
        tmp->free_memory();
    }

    template <typename T>
    void list<T>::push_front(T data) {
        // listNode second(this->head_->data, this->head_->pNext, head_);
        if (size_ == 0) {
            head_ = new node;
            head_->pNext = nullptr;
            head_->pPrev = nullptr;
            head_->data = data;
            ++size_;
        } else {
            // node *p = head_;
            // node *first = new node;
            // tmp->pPrev = p;
            // tmp->pNext = nullptr;
            // tmp->data = data;
            // p->pNext = tmp;
            // ++size_;
            node *second = new node;
            second->data = head_->data;
            second->pNext = head_->pNext;
            second->pPrev = head_;

            head_->data = data;
            head_->pPrev = nullptr;
            head_->pNext = second;
            size_++;
        }
    }

    template <typename T>
    void list<T>::pop_front() {
        head_->data = head_->pNext->data;
        head_->pNext->data = 0;
        node *del = head_->pNext;
        head_->pNext= head_->pNext->pNext;
        node *second = head_->pNext->pNext;
        second->pPrev = head_;
        del->free_memory();
        size_--;
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
        this->clear();
        head_ = new node();
        list<T>::ListIterator ptr(other);
        while (ptr.itr) {
            push_back(*ptr);
            ptr++;
        }
        return *this;
    }
    
    template <typename T>
    T& list<T>::front() const {
        list<T>::ListIterator tmp(*this);
        return *tmp;
    }

    template <typename T>
    T& list<T>::back() const {
        ListIterator tmp = this.end();
        return *tmp;
    }

    template <typename T>
    void list<T>::reverse() {
        list<T> ptr;
        list<T>::ListIterator tmp = this->begin();
        // for (auto c = tmp.end; tmp.itr != c; tmp++) {
        //     ptr.push_front(*tmp);
        // }
        int count = size_;
        for (auto c = tmp.end; count > 0; tmp++) {
            ptr.push_front(*tmp);
            count--;
        }
        *this = ptr;
    }

    template <typename T>
    void list<T>::unique() {
        list<T>::ListIterator ptr = this->begin();
        auto c = ptr.itr;
        node *second = nullptr;
        ptr++;
        while (ptr.itr) {
            if (c->data == ptr.itr->data) {
                if (second) {
                second->pNext = ptr.itr->pNext;
                ptr.itr->pNext->pPrev = second; 
                ptr.itr->free_memory();
                size_--;
                ptr++;
                continue;
                } else {
                    pop_front();
                    ptr = begin();
                    second = ptr.itr;
                    ptr++;
                    continue;
                }
            }
            c = ptr.itr;
            second = ptr.itr;
            ptr++;
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
        node* tmp;
        tmp = other.head_;
        other.head_ = head_;
        head_ = tmp;
        int tmp_size = other.size_;
        other.size_ = size_;
        size_ = tmp_size;
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
        return itr == other.iter;
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
        ListIterator tmp = (*this);
        while (tmp.itr != nullptr) {
            tmp++;
        }
        return tmp;
    }

    template <typename T>
    typename list<T>::ListIterator list<T>::insert (ListIterator pos, const T& value) {
        // нужно реализовать        
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
        iterator ptr = *this;
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
        iterator ptr = *this;
        itr = itr->pPrev;
        return ptr;
    }
    
    template <typename T>
    bool list<T>::ListConstIterator:: operator== (const ListConstIterator& other) {
        return itr == other.iter;
    }

    template <typename T>
    bool list<T>::ListConstIterator:: operator!= (const ListConstIterator& other) {
        return itr != other.iter;
    }

    template <typename T>
    typename list<T>::const_iterator  list<T>::cbegin() const{
        return ListConstIterator(*this);
    }

    template <typename T>
    typename list<T>::const_iterator  list<T>::cend() const{
        ListConstIterator tmp = (*this);
        while (tmp.itr != tmp.end) {
            tmp++;
        }
        return ListConstIterator(tmp);
    }
    
} // namespace s21























        //   r_j != pivot);
        //   if (size_ < 2) return;
        // list<T>::ListIterator ptr_i = this->begin();
        // list<T>::ListIterator ptr_j = this->end();
        // list<T>::ListIterator pivot = this->begin();
        // int count = size_/2;
        // while (count-->0) {
        //     pivot++;
        // }
        // T value = *pivot;
        // list<T> left;
        // list<T> right;


        // while (ptr_i.itr != ptr_j.end)
        // {
        //     while (ptr_i.itr->data < value)
        //         ptr_i++;
        //     while (ptr_j.end->data > value)
        //         ptr_j--;
        //     if (ptr_i.itr->data <= ptr_j.itr->data)
        //     {
        //         ptr_i.swap_elements(ptr_j);
        //         ptr_i++;
        //         ptr_j--;
        //     }
        // }
        // if (ptr_j.itr > ptr_j.first)
        //     // sort();
        // if (ptr_i.itr < ptr_j.end)
        //     // sort();
        
        // left.sort();
        // right.sort();
        // left.merge(right);
        // *this = left;
    
    // void quickSort(int *array, int low, int high) {
    //     int i = low;
    //     int j = high;
    //     int pivot = array[(i + j) / 2];
    //     int temp;

    //     while (i <= j)
    //     {
    //         while (array[i] < pivot)
    //             i++;
    //         while (array[j] > pivot)
    //             j--;
    //         if (i <= j)
    //         {
    //             temp = array[i];
    //             array[i] = array[j];
    //             array[j] = temp;
    //             i++;
    //             j--;
    //         }
    //     }
    //     if (j > low)
    //         quickSort(array, low, j);
    //     if (i < high)
    //         quickSort(array, i, high);
    // }




        // while (ptr_i != ptr_j) {
        //     if (*ptr_i > value) {
        //         right.push_back(*ptr_i);
        //     } else {
        //         left.push_back(*ptr_i);
        //     }
        //     ptr_i++;
        // }

        // do {
        //     while(*ptr_i < value) {
        //         ptr_i++;
        //     }
        //     while(*ptr_j.end > value) {
        //         ptr_j--;
        //     }
        //     if (*ptr_i >= *ptr_j) {
        //         ptr_i.swap_elements(ptr_j);
        //         ptr_i++;
        //         ptr_j--;
        //     }
        // } while (ptr_i != pivot || pt