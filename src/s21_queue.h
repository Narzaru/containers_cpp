#pragma once
#include "./s21_list.h"

namespace s21 {
template <typename T, class s21_queue = s21::list<T>>
class queue {
 private:
    s21_queue A;
 public:
    typedef typename s21_queue::value_type value_type;
    typedef typename s21_queue::reference reference;
    typedef typename s21_queue::const_reference const_reference;
    typedef typename s21_queue::size_type size_type;

    queue(): A() {};
    queue(std::initializer_list<T> const& items): A(items) {};
    queue(const queue &q): A(q.A) {};
    queue(queue &&q): A(std::move(q.A)) {};
    ~queue() {
    };

    queue<T>& operator=(queue &&q) {
        this->A = q.A;
        return *this;
    }

    void push(const_reference value) {A.push_back(value);}
    void pop() {A.pop_front();}
    void swap(queue& other) {A.swap(other.A);}

    const_reference front() {
        return A.front();
    }

    const_reference back() {
        return A.back();
    }

    bool empty() {
        return A.empty();
    }
    
    size_type size();

};

}