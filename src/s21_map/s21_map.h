#pragma once
#include <cstddef>
#include <initializer_list>
#include "../s21_sorted_tree/s21_sorted_tree.h"

namespace s21 {
    template <typename Key, typename T>
    class map : public sorted_tree<Key, T> {
    
     public:
        using value_type = std::pair<Key, T>;
        using iterator = typename sorted_tree<Key, T>::Iterator;
        
        // Map Member functions
        map<Key, T>();
        map<Key, T>(std::initializer_list<value_type> const &items);
        map(const map &m);
        map(map &&m);
        ~map();
        map<Key, T> & operator=(map &&m);

        // Map Element access
        T& at(const Key& key);
        T& operator[](const Key& key);
   
        // Map Modifiers
        std::pair<iterator, bool> insert(const value_type& value);
        std::pair<iterator, bool> insert(const Key& key, const T& obj);
        std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);

        void merge(map& other);

     

    };
    

} // namespace s21

#include "s21_map.inl"