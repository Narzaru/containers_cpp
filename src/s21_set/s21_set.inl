namespace s21 {
    template <typename Key, typename Value>
    set<Key, Value>::set() : sorted_tree<Key, Value>() {}

    template <class Key, class Value>
    set<Key, Value>::set(std::initializer_list<value_type> const &items) : sorted_tree<Key, Value>::sorted_tree() {
        for (const auto &data:items)
            this->insert(data);
    }
    
    template <class Key, class Value>
    set<Key, Value>::set(const set<Key, Value>& other) : sorted_tree<Key, Value>(other) {}

    template <class Key, class Value>
    set<Key, Value>::set(set<Key, Value>&& other) : sorted_tree<Key, Value>::sorted_tree(std::move(other)) {}

    template <class Key, class Value>
    set<Key, Value>::~set() {}

    template <class Key, class Value>
    set<Key, Value>& set<Key, Value>::operator=(const set& other) {
        sorted_tree<Key, Value>::operator=(other);
        return *this;
    }

    template <class Key, class Value>
    set<Key, Value>& set<Key, Value>::operator=(set&& other) {
        sorted_tree<Key, Value>::operator=(std::move(other));
        return *this;
    }

    template <class Key, class Value>
    std::pair<typename set<Key, Value>::iterator, bool> set<Key, Value>::insert(const value_type& value) {
        iterator result_itr = this->find(value);
        bool is_inserted = false;
        if (result_itr.itr == this->nil) {
            result_itr = this->insert_pair(std::make_pair(value, Value()));
            is_inserted = true;
        }
        return std::pair(result_itr, is_inserted);
    }

    template <class Key, class Value>
    void set<Key, Value>::merge(set& other) {
        iterator ptr(other);
        while (ptr.itr != ptr.end) {
            insert(ptr.itr->key);
            ++ptr;
        }
    }

    // template <class Key, class Value>
    // template <typename Key, typename Value>
    // std::pair<Key, Value> set<Key, Value>::Iterator::operator* () const {
    //     if (itr == nullptr) {
    //         throw std::out_of_range("Container is empty");
    //     }
    //     return std::pair(itr->key, itr->value);
    // }


}