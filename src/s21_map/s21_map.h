#pragma once
#include <cstddef>
#include <initializer_list>
#include "../s21_sorted_tree/s21_sorted_tree.h"

namespace s21 {
    template <typename Key, typename Value>
    class map : public sorted_tree<Key, Value> {
    
     public:
        using value_type = std::pair<Key, Value>;
        using iterator = typename sorted_tree<Key, Value>::Iterator;
        using const_iterator = typename sorted_tree<Key, Value>::ConstIterator;
        
        // Map Member functions
        map<Key, Value>();
        map<Key, Value>(std::initializer_list<value_type> const &items);
        map(const map &m);
        map(map &&m);
        ~map();
        map<Key, Value> & operator=(const map &m);
        map<Key, Value> & operator=(map &&m);

        // Map Element access
        Value& at(const Key& key);
        Value& operator[](const Key& key);
   
        // Map Modifiers
        std::pair<iterator, bool> insert(const value_type& value);
        std::pair<iterator, bool> insert(const Key& key, const Value& obj);
        std::pair<iterator, bool> insert_or_assign(const Key& key, const Value& obj);

        void merge(map& other);

        template <typename... Args>
        inline std::pair<iterator, bool> emplace(Args &&...args) {
            return insert(value_type(std::forward<Args>(args)...));
        }
    };
    

} // namespace s21

#include "s21_map.inl"