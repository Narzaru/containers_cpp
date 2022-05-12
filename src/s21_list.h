#pragma once
#include <cstddef>
#include <initializer_list>

namespace s21 {

    template <typename T>
    class list {

     public:
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;

        void print_cont();
        bool emply();
        size_t size();
        size_t max_size();
        void clear(); 
        void push_back (T data);
        void pop_back();
        void push_front(T data);
        void pop_front();
        void reverse();
        void swap(list& other);
        void unique();
        void sort();
        void merge(list& other);


        T& front() const;
        T& back() const;



        list& operator=(list& other);

        list<T>();
        list<T>(size_t n);
        list<T>(std::initializer_list<T> const& items);
        list<T>(list &&l);
        list(const list &l);
        
        ~list() {
            clear();
        }

        class listNode {
         public:
            listNode *pNext;
            listNode *pPrev;

            listNode(T data = T(), listNode *pNext = nullptr, listNode *pPrev = nullptr) { // конструктор
                this->data = data;
                this->pNext = pNext;
                this->pPrev = pPrev;
            }

            ~listNode() {
                free_memory();
            }
            
            T data; 
            void free_memory();
        };
        typedef list<T>::listNode node;

        class ListIterator {
         public:
            node* first;        //первый
            node* end;          //последний
            node* itr;          //текущий
            
            ListIterator() {
                first = nullptr;
                end = nullptr;
                itr = nullptr;
            };
            ListIterator(const list<T>& other) {
                first = other.head_;
                end = other.back_;
                itr = other.head_;
            };
            ~ListIterator() {
                free_iterator();
            };
            void swap_elements(ListIterator pos);
            void free_iterator();
            T& operator*() const;
            ListIterator operator++();
            ListIterator operator++(int);
            ListIterator operator--();
            ListIterator operator--(int);
            bool operator==(const ListIterator& other);
            bool operator!=(const ListIterator& other);
        };
        typedef typename list<T>::ListIterator iterator;

        iterator begin();
        iterator end();
        iterator insert(iterator pos, const_reference value);

        class ListConstIterator {
         public:
            node* first;        //первый
            node* end;          //последний
            node* itr;          //текущий
            
            ListConstIterator() {
                first = nullptr;
                end = nullptr;
                itr = nullptr;
            };
            ListConstIterator(const list<T>& other) {
                first = other.head_;
                end = other.back_;
                itr = other.head_;
            };
            ~ListConstIterator() {
                free_iterator();
            };
            
            void free_iterator();
            T& operator*() const;
            ListConstIterator operator++();
            ListConstIterator operator++(int);
            ListConstIterator operator--();
            ListConstIterator operator--(int);
            bool operator==(const ListConstIterator& other);
            bool operator!=(const ListConstIterator& other);
        };
        typedef typename list<T>::ListConstIterator const_iterator;

        const_iterator cbegin() const;
        const_iterator cend() const;
        
     private:

        size_t size_;               // максимальный размер
        node* head_;
        node* back_;                // реализовать присваивание 
        void last_node();
    };

} // namespace s21
#include "s21_list.inl"
