namespace s21 {
    template <typename Key, typename Value>
    multiset<Key, Value>::multiset() : sorted_tree<Key, Value>() {}

    template <class Key, class Value>
    multiset<Key, Value>::multiset(std::initializer_list<value_type> const &items)
    : sorted_tree<Key, Value>::sorted_tree() {
        for (const auto &data : items)
            this->insert(data);
    }

    template <class Key, class Value>
    multiset<Key, Value>::multiset(const multiset<Key, Value>& other) : sorted_tree<Key, Value>(other) {}

    template <class Key, class Value>
    multiset<Key, Value>::multiset(multiset<Key, Value>&& other)
    : sorted_tree<Key, Value>::sorted_tree(std::move(other)) {}

    template <class Key, class Value>
    multiset<Key, Value>::~multiset() {}

    template <class Key, class Value>
    multiset<Key, Value>& multiset<Key, Value>::operator=(const multiset& other) {
        sorted_tree<Key, Value>::operator=(other);
        return *this;
    }

    template <class Key, class Value>
    multiset<Key, Value>& multiset<Key, Value>::operator=(multiset&& other) {
        sorted_tree<Key, Value>::operator=(std::move(other));
        return *this;
    }

    template <class Key, class Value>
    typename multiset<Key, Value>::iterator multiset<Key, Value>::insert(const value_type& value) {
        return this->insert_pair(std::make_pair(value, Value()));
    }

    template <class Key, class Value>
    void multiset<Key, Value>::merge(multiset& other) {
        iterator ptr(other);
        while (ptr.itr != ptr.end) {
            insert(ptr.itr->key);
            ++ptr;
        }
        other.reset();
    }

}  // namespace s21
