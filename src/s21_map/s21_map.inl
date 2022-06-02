namespace s21 {
    template <class Key, class Value>
    map<Key, Value>::map() : sorted_tree<Key, Value>::sorted_tree() {}

    template <class Key, class Value>
    map<Key, Value>::map(const map<Key, Value>& other) : sorted_tree<Key, Value>::sorted_tree(other) {}

    template <class Key, class Value>
    map<Key, Value>::~map() {}

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
}