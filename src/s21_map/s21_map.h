#pragma once
#include <cstddef>
#include <initializer_list>

namespace s21 {
    template <typename Key, typename T>
    class map
    {
    
     public:
        // Map Member type
        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<const key_type, mapped_type>;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = MapIterator<Key, T>;
        using const_iterator = MapConstIterator<Key, T>;
        using size_type = std::size_t;

        // Map Member functions
        map<Key, T>();
        map<Key, T>(std::initializer_list<value_type> const &items);
        map(const map &m);
        map(map &&m);
        ~map();
        operator=(map &&m);

        // Map Element access
        T& at(const Key& key);
        T& operator[](const Key& key);

        // Map Iterators
        iterator begin();
        iterator end();

        // Map Capacity
        bool empty();
        size_type size();
        size_type max_size();

        // Map Modifiers
        void clear();
        std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
        void erase(iterator pos);
        void swap(map& other);
        void merge(map& other);

        // Map Lookup
        bool contains(const Key& key);


     private:
        iterator array_;
        size_type size_;
        size_type capacity_;

        class Node {
         public:
            Node *parent;
            Node *left_child;
            Node *right_child;

            Key key;
            T value;

            Node(Key key = Key(), T value = T(), Node *parent = nullptr, Node *left_child = nullptr, Node *right_child = nullptr) {
                this->key = key;
                this->value = value;
                this->parent = parent;
                this->left_child = left_child;
                this->right_child = right_child;
            }
            ~Node();
        }
    };
    

} // namespace s21

#include "s21_map.inl"