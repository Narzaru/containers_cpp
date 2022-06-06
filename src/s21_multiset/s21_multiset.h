#ifndef SRC_S21_MULTISET_S21_MULTISET_H_
#define SRC_S21_MULTISET_S21_MULTISET_H_

#pragma once
#include "../s21_sorted_tree/s21_sorted_tree.h"

namespace s21 {
    template <typename Key, typename Value = int>
    class multiset : public s21::sorted_tree<Key, Value> {
     public:
        using value_type = Key;
        using iterator = typename sorted_tree<Key, Value>::Iterator;
        using const_iterator = typename sorted_tree<Key, Value>::ConstIterator;


        multiset();
        multiset(std::initializer_list<value_type> const &items);
        multiset(const multiset &s);
        multiset(multiset &&s);
        multiset & operator=(const multiset& s);
        multiset & operator=(multiset&& s);
        ~multiset();

        iterator insert(const value_type& value);
        void merge(multiset& other);

        using sorted_tree<Key, Value>::find;

        using sorted_tree<Key, Value>::equal_range;
        using sorted_tree<Key, Value>::lower_bound;
        using sorted_tree<Key, Value>::upper_bound;

        template <typename... Args>
        inline iterator emplace(Args &&...args) {
            return insert(value_type(std::forward<Args>(args)...));
        }
    };
}  // namespace s21

#include "s21_multiset.inl"

#endif  // SRC_S21_MULTISET_S21_MULTISET_H_
