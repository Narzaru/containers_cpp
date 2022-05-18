namespace s21 {
    template<typename Key>
    set<Key>::set() : size_(0) {
        nil = new Node();
        root_ = nil;
        max_size_ = std::numeric_limits<std::size_t>::max() / sizeof(Key);
    }

    template <typename Key>
    void set<Key>::clear() {
        if (root_->left_child != nil) delete root_->left_child;
        if (root_->right_child != nil) delete root_->right_child;
        if (root_->parent != nil) delete root_->parent;
        delete root_;
    } 

    template <typename Key>
    set<Key>& set<Key>::operator=(set& other) {
        
        return *this;
    }


    template<typename Key>
    typename set<Key>::Node *set<Key>::SetIterator::find_first(const set<Key> &other) {
        Node *current_child = other.root_;
        if (other.root_ != other.nil && other.root_->left_child != other.nil) {
            Node *current_child = other.root_->left_child;
            while (current_child->left_child != other.nil) {
                current_child = current_child->left_child;
            }
        }
        return current_child;
    }

    template<typename Key>
    typename set<Key>::iterator set<Key>::begin() {
        iterator iter(*this);
        return iter;
    }

    template<typename Key>
    typename set<Key>::iterator set<Key>::end() {
        return nil;
    }

    template<typename Key>
    bool set<Key>::empty() const {
        return size_ == 0;
    }

    template<typename Key>
    typename set<Key>::size_type set<Key>::size() const {
        return size_;
    }

    template<typename Key>
    typename set<Key>::size_type set<Key>::max_size() const {
        return size_;
    }

    template<typename Key>
    std::pair<typename set<Key>::iterator, bool> set<Key>::insert(const value_type& value) {
        std::pair<iterator, bool> result;
        if (root_ == nil) {
            root_ = new Node(value, BLACK, nullptr, nil, nil);
            result.first = this->begin();
            result.second = true;
            size_++;
        }
        return result;
    }

    template <typename Key>
    Key& set<Key>::SetIterator::operator* () const {
        if (itr == nullptr) {
            // бросить исключение
        }
        return itr->key;
    }


    // template<typename Key>
    // typename set<Key>::iterator set<Key>::find(const Key& key) {
    //     iterator result = end();
    //     if (root_ != nil) {
    //         Node *current_node = root_;
    //         while (current_node->key != key || (current_node->left_child == nil && current_node->key < key) || (current_node->right_child == nil && current_node->key > key)) {
    //             if (current_node->key < key) current_node = current_node->left_child;
    //             else current_node = current_node->right_child;
    //         }
    //         if (current_node->key == key) result = current_node;
            
    //     }
    //     return result;
    // }

    template<typename Key>
    bool set<Key>::contains(const Key& key) {
        bool result = true;
        if (find(key) == end()) result == false;
        return result;
    }

}