namespace s21 {
    template <class Key, class Value>
    map<Key, Value>::map() : sorted_tree<Key, Value>::sorted_tree() {}

    template <class Key, class Value>
    map<Key, Value>::map(const map<Key, Value>& other) : sorted_tree<Key, Value>::sorted_tree(other) {}

    template <class Key, class Value>
    map<Key, Value>::map(map<Key, Value>&& other) : sorted_tree<Key, Value>::sorted_tree(std::move(other)) {}

    template <class Key, class Value>
    map<Key, Value>::map(std::initializer_list<value_type> const &items)
    : sorted_tree<Key, Value>::sorted_tree() {
        for (const auto &data : items)
            this->insert(data);
    }

    template <class Key, class Value>
    map<Key, Value>::~map() {}

    template <class Key, class Value>
    map<Key, Value>& map<Key, Value>::operator=(const map& other) {
        sorted_tree<Key, Value>::operator=(other);
        return *this;
    }

    template <class Key, class Value>
    map<Key, Value>& map<Key, Value>::operator=(map&& other) {
        sorted_tree<Key, Value>::operator=(std::move(other));
        return *this;
    }


    template <class Key, class Value>
    std::pair<typename map<Key, Value>::iterator, bool> map<Key, Value>::insert(const value_type& value) {
        iterator result_itr = this->find(value.first);
        bool is_inserted = false;
        if (result_itr.itr == this->nil) {
            result_itr = this->insert_pair(value);
            is_inserted = true;
        }
        return std::pair(result_itr, is_inserted);
    }


    template <class Key, class Value>
    Value& map<Key, Value>::at(const Key& key) {
        iterator iter = this->find(key);
        if (iter.itr == this->nil) {
            throw std::out_of_range("No such element");
        }
        return iter.itr->value;
    }

    template <class Key, class Value>
    Value& map<Key, Value>::operator[](const Key& key) {
        return at(key);
    }

    template <class Key, class Value>
    std::pair<typename map<Key, Value>::iterator, bool>
    map<Key, Value>::insert(const Key& key, const Value& obj) {
        return insert(std::pair(key, obj));
    }

    template <class Key, class Value>
    std::pair<typename map<Key, Value>::iterator, bool>
    map<Key, Value>::insert_or_assign(const Key& key, const Value& obj) {
        iterator result_itr = this->find(key);
        bool is_inserted = false;
        if (result_itr.itr == this->nil) {
            result_itr = this->insert_pair(std::pair(key, obj));
            is_inserted = true;
        } else {
            result_itr.itr->value = obj;
        }
        return std::pair(result_itr, is_inserted);
    }

    template <class Key, class Value>
    void map<Key, Value>::merge(map<Key, Value>& other) {  // NOLINT(*)
      iterator ptr(other);
      while (ptr.itr != ptr.end) {
        insert(ptr.itr->key, ptr.itr->value);
        ++ptr;
      }
      other.clear();
    }
}  // namespace s21
