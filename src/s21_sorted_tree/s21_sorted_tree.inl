namespace s21 {
    template<typename Key, typename Value>
    sorted_tree<Key, Value>::sorted_tree() : size_(0) {
        set_initial_properties();
    }

    template <typename Key, typename Value>
    sorted_tree<Key, Value>::sorted_tree(const sorted_tree<Key, Value> &other) : size_(0) {
        set_initial_properties();
        sorted_tree<Key, Value>::Iterator ptr(other);
        while (ptr.itr != ptr.end) {
            insert(*ptr);
            ++ptr;
        }
    };

    template<typename Key, typename Value>
    sorted_tree<Key, Value>::sorted_tree(sorted_tree<Key, Value> &&other) {
        max_size_ = other.max_size_;
        root_ = other.root_;
        nil = other.nil;
        size_ = other.size_;
        other.root_ = nullptr;
        other.nil = nullptr;
    }

    template<typename Key, typename Value>
    sorted_tree<Key, Value> &sorted_tree<Key, Value>::operator=(const sorted_tree<Key, Value> &other) {
        reset();
        sorted_tree<Key, Value>::Iterator ptr(other);
        while (ptr.itr != ptr.end) {
            insert(*ptr);
            ++ptr;
        }
        return *this;
    }

    template<typename Key, typename Value>
    sorted_tree<Key, Value> &sorted_tree<Key, Value>::operator=(sorted_tree<Key, Value> &&other) {
        free_sorted_tree();
        root_ = other.root_;
        nil = other.nil;
        size_ = other.size_;
        max_size_ = other.max_size_;
        other.root_ = nullptr;
        other.nil = nullptr;
        other.size_ = 0;
        return *this;
    }

    template <typename Key, typename Value>
    void sorted_tree<Key, Value>::free_sorted_tree() {
        clear();
        delete nil;
        nil = nullptr;
    }

    template <typename Key, typename Value>
    void sorted_tree<Key, Value>::reset() {
        if (root_ != nullptr) {
            clear();
            delete nil;
            nil = nullptr;
        }
        if (nil == nullptr) set_initial_properties();
    }

    template <typename Key, typename Value>
    void sorted_tree<Key, Value>::set_initial_properties() {
        nil = new Node();
        root_ = nullptr;
        max_size_ = std::numeric_limits<size_type>::max() / sizeof(Key);
    }

    template <typename Key, typename Value>
    void sorted_tree<Key, Value>::clear() {
        if (root_) {
            root_->free_node_recursive(root_, nil);
            size_ = 0;
        }
        // delete nil;
    }

    template <typename Key, typename Value>
    void sorted_tree<Key, Value>::Node::free_node() {
        parent = nullptr;
        left_child = nullptr;
        right_child = nullptr;
        key = Key();
        value = Value();
        color = RED;
    }

    template <typename Key, typename Value>
    void sorted_tree<Key, Value>::Node::free_node_recursive(Node* node, Node *nil) {
        node->parent = nullptr;
        if (node->left_child != nil) free_node_recursive(node->left_child, nil);
        if (node->right_child != nil) free_node_recursive(node->right_child, nil);
        node->left_child = nullptr;
        node->right_child = nullptr;
        // node->key = key_type();
        // node->value = value_type();
        // node->color = RED;
        delete node;
        node = nullptr;
    }

    template <typename Key, typename Value>
    void sorted_tree<Key, Value>::swap(sorted_tree<Key, Value>& other) {
        // sorted_tree<Key, Value> *temp;
        Node *tmp = other.root_;
        other.root_ = root_;
        root_ = tmp;
        tmp = other.nil;
        other.nil = nil;
        nil = tmp;
        int tmp_size = other.size_;
        other.size_ = size_;
        size_ = tmp_size;
    }

    template<typename Key, typename Value>
    typename sorted_tree<Key, Value>::Node *sorted_tree<Key, Value>::find_node_to_insert(const value_type& value) {
        Node *current_node = root_;
        while (current_node->key > value.first && current_node->left_child != nil || current_node->key < value.first && current_node->right_child != nil) {
            if (current_node->key > value.first) current_node = current_node->left_child;
            else current_node = current_node->right_child;
        }
        return current_node;
    }

    template<typename Key, typename Value>
    typename sorted_tree<Key, Value>::iterator sorted_tree<Key, Value>::insert_pair(const value_type& value) {
        iterator result;
        // Node *new_node = new Node();
        if (root_ == nullptr) {
            root_ = new Node(value.first, value.second, BLACK, nullptr, nil, nil);;
            result = this->begin();
            size_++;
        } else {
            Node *current_node = find_node_to_insert(value);
            if (current_node->key == value.first) {
                current_node->number_of_similar++;
            } else {
                Node *new_node = new Node(value.first, value.second, RED, current_node, nil, nil);
                if (current_node->key > value.first) {
                    current_node->left_child = new_node;
                    current_node = current_node->left_child;
                } else {
                    current_node->right_child = new_node;
                    current_node = current_node->right_child;
                }
                fix_up_insert(current_node);
            }
            size_++;
            result = this->begin();
            iterator *current_iterator = &result;
            current_iterator->itr = current_node;
            current_iterator->current_node_iteration = current_node->number_of_similar;
        }
        return result;
    }

    template<typename Key, typename Value>
    void sorted_tree<Key, Value>::rotate_left(Node *node) {
        Node *right = node->right_child;
        node->right_child = right->left_child;
        if (right->left_child != nil) right->left_child->parent = node;
        right->parent = node->parent;
        if (node->parent == nullptr) {
            root_ = right;
        } else {
            if (node == node->parent->left_child)
                node->parent->left_child = right;
            else
                node->parent->right_child = right; 
        }
        right->left_child = node;
        node->parent = right;
    }

    template<typename Key, typename Value>
    void sorted_tree<Key, Value>::rotate_right(Node *node) {
        Node *left = node->left_child;
        node->left_child = left->right_child;
        if (left->right_child != nil) left->right_child->parent = node;
        left->parent = node->parent;
        if (node->parent == nullptr) {
            root_ = left;
        } else {
            if (node == node->parent->right_child)
                node->parent->right_child = left;
            else
                node->parent->left_child = left; 
        }
        left->right_child = node;
        node->parent = left;
    }
    
    
    template<typename Key, typename Value>
    void sorted_tree<Key, Value>::fix_up_insert(Node *node) {
        Node *parent = node->parent;
        while (node != root_ && parent->color == RED) {
            Node *gparent = parent->parent;
            if (gparent->left_child == parent) {
                Node *uncle = gparent->right_child;
                if (uncle != nil && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    gparent->color = RED;
                    node = gparent;
                    parent = node->parent;
                } else {
                    if (parent->right_child == node) {
                        rotate_left(parent);
                        std::swap(node, parent);
                    }
                    rotate_right(gparent);
                    gparent->color = RED;
                    parent->color = BLACK;
                    break;
                }
            } else {
                Node *uncle = gparent->left_child;
                if (uncle != nil && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    gparent->color = RED;

                    node = gparent;
                    parent = node->parent;
                } else {
                    if (parent->left_child == node) {
                        rotate_right(parent);
                        std::swap(parent, node);
                    }
                    rotate_left(gparent);
                    gparent->color = RED;
                    parent->color = BLACK;
                    break;
                }
            }
        }
        root_->color = BLACK;        
    }

    template<typename Key, typename Value>
    void sorted_tree<Key, Value>::erase(typename sorted_tree<Key, Value>::Iterator pos) {
        if (pos.itr && pos.itr != pos.end) {
            if (pos.itr->number_of_similar > 1) {
                pos.itr->number_of_similar--;
            } else {
                erase_existing(pos);
            }
            size_--;
            // pos.itr = nullptr;
        }
    }

    template<typename Key, typename Value>
    void sorted_tree<Key, Value>::erase_existing(iterator pos) {
        Node *node = pos.itr;
        Node *child, *parent;
        node_color color;
        if (node->left_child != nil && node->right_child != nil) {
            Node *replace = pos.find_lowest_child(node->right_child);
            if (node->parent != nullptr) {
                if (node->parent->left_child == node)
                    node->parent->left_child = replace;
                else
                    node->parent->right_child = replace;
            } else {
                root_ = replace;
            }
            child = replace->right_child;
            parent = replace->parent;
            color = replace->color;

            if (parent == node) {
                parent = replace;
            } else {
                if (child != nil) child->parent = parent;
                parent->left_child = child;

                replace->right_child = node->right_child;
                node->right_child->parent = replace;
            }
            replace->parent = node->parent;
            replace->color = node->color;
            replace->left_child = node->left_child;
            node->left_child->parent = replace;
        } else {
            if (node->left_child != nil)
                child = node->left_child;
            else
                child = node->right_child;
            
            parent = node->parent;
            color = node->color;
            
            if (child != nil) child->parent = parent;
            if (parent) {
                if (node == parent->left_child)
                    parent->left_child = child;
                else
                    parent->right_child = child;
            } else {
                root_ = child;
            }
        }
        if (color == BLACK) {
            fix_up_erase(child, parent);
        }
        delete node;
    }

    template<typename Key, typename Value>
    void sorted_tree<Key, Value>::fix_up_erase(Node *node, Node *parent) {
        Node *other;
        while (!node || node->color == BLACK && node != root_) {
            if (parent->left_child == node) {
                other = parent->right_child;
                if (other->color == RED) {
                    other->color = BLACK;
                    parent->color = RED;
                    rotate_left(parent);
                    other = parent->right_child;
                } else {
                    if (other->right_child == nil || other->color == BLACK) {
                        other->left_child->color = BLACK;
                        other->color = RED;
                        rotate_right(other);
                        other = parent->right_child;
                    }
                    other->color = parent->color;
                    parent->color = BLACK;
                    other->right_child->color = BLACK;
                    rotate_left(parent);
                    node = root_;
                    break;
                }
            } else {
                other = parent->left_child;
                if (other->color == RED) {
                    other->color = BLACK;
                    parent->color = RED;
                    rotate_right(parent);
                    other = parent->left_child;
                }
                if (other->left_child->color == BLACK && other->right_child->color == BLACK) {
                    other->color = RED;
                    node = parent;
                    parent = node->parent;
                } else {
                    if (other->left_child->color = BLACK) {
                        other->right_child->color = BLACK;
                        other->color = RED;
                        rotate_left(other);
                        other = parent->left_child;
                    }
                    other->color = parent->color;
                    parent->color = BLACK;
                    other->left_child->color = BLACK;
                    rotate_right(parent);
                    node = root_;
                    break;
                }
            }
        }
        if (node) node->color = BLACK;
    }


    template<typename Key, typename Value>
    bool sorted_tree<Key, Value>::empty() const {
        return size_ == 0;
    }

    template<typename Key, typename Value>
    typename sorted_tree<Key, Value>::size_type sorted_tree<Key, Value>::size() const {
        return size_;
    }

    template<typename Key, typename Value>
    typename sorted_tree<Key, Value>::size_type sorted_tree<Key, Value>::max_size() const {
        return max_size_;
    }

    template<typename Key, typename Value>
    typename sorted_tree<Key, Value>::Node *sorted_tree<Key, Value>::Iterator::find_lowest_child(Node *node) {
        Node *current_child = node;
        if (node && node != nil && node->left_child != nil) {
            current_child = node->left_child;
            while (current_child->left_child != nil) {
                current_child = current_child->left_child;
            }
        }
        return current_child;
    }

    template<typename Key, typename Value>
    typename sorted_tree<Key, Value>::Node *sorted_tree<Key, Value>::Iterator::find_highest_child(Node *node) {
        Node *current_child = node;
        if (node && node != nil && node->right_child != nil) {
            current_child = node->right_child;
            while (current_child->right_child != nil) {
                current_child = current_child->right_child;
            }
        }
        return current_child;
    }

    template<typename Key, typename Value>
    typename sorted_tree<Key, Value>::iterator sorted_tree<Key, Value>::find(const Key& key) {
        iterator result = this->begin();
        if (root_ && root_ != nil) {
            Node *current_node = root_;
            while (current_node->key != key && (current_node->left_child != nil && current_node->key > key || current_node->right_child != nil && current_node->key < key)) {
                if (current_node->key > key) current_node = current_node->left_child;
                else current_node = current_node->right_child;
            }
            if (current_node->key == key) result.itr = current_node;
            else result.itr = result.end;
            
        }
        return result;
    }

    template<typename Key, typename Value>
    bool sorted_tree<Key, Value>::contains(const Key& key) {
        iterator current = find(key);
        return current.end && current.itr != current.end;
    }

    template<typename Key, typename Value>
    typename sorted_tree<Key, Value>::iterator sorted_tree<Key, Value>::begin() {
        iterator iter(*this);
        return iter;
    }

    template<typename Key, typename Value>
    typename sorted_tree<Key, Value>::iterator sorted_tree<Key, Value>::end() {
        iterator iter(*this);
        iter.itr = iter.end;
        return iter;
    }

    template<typename Key, typename Value>
    typename sorted_tree<Key, Value>::const_iterator sorted_tree<Key, Value>::cbegin() const {
        const_iterator iter(*this);
        return iter;
    }

    template<typename Key, typename Value>
    typename sorted_tree<Key, Value>::const_iterator sorted_tree<Key, Value>::cend() const {
        const_iterator iter(*this);
        iter.itr = iter.end;
        return iter;
    }

    // ITERATOR

    template <typename Key, typename Value>
    void sorted_tree<Key, Value>::Iterator::nullify_iterator_properties() {
        first = nullptr;
        end = nullptr;
        itr = nullptr;
        nil = nullptr;
        current_node_iteration = 1;
    }

    template <typename Key, typename Value>
    void sorted_tree<Key, Value>::Iterator::free_iterator() {
        nullify_iterator_properties();
    }

    template <typename Key, typename Value>
    std::pair<Key, Value> sorted_tree<Key, Value>::Iterator::operator* () const {
        if (itr == nullptr) {
            throw std::out_of_range("Container is empty");
        }
        return std::pair(itr->key, itr->value);
    }

    template <typename Key, typename Value>
    typename sorted_tree<Key, Value>::Iterator sorted_tree<Key, Value>::Iterator::operator++() {
        if (itr && itr->left_child) {
            if (current_node_iteration < itr->number_of_similar) {
                current_node_iteration++;
            } else {
                Node *parent = itr->parent;
                current_node_iteration = 1;
                if (itr != nil) {
                    if (itr->right_child != nil) {
                        itr = itr->right_child;
                        if (itr->left_child != nil) itr = find_lowest_child(itr->left_child);
                    } else if (!parent) {
                        itr = end;
                    } else if (parent->left_child == itr) {
                        itr = itr->parent;
                    } else if (parent->right_child == itr) {
                        Node *higher_volume_parent = find_higher_volume_parent(parent);
                        if (higher_volume_parent) itr = higher_volume_parent;
                        else itr = end;
                    }
                }
            }
            
        }
        return *this;
    }

    template <typename Key, typename Value>
    typename sorted_tree<Key, Value>::Iterator sorted_tree<Key, Value>::Iterator::operator--() {
        Node *parent = itr->parent;
        if (itr == end) {
            itr = itr->parent;
        } else {
            if (current_node_iteration > 1) {
                current_node_iteration--;
            } else {
                if (itr->left_child != nil) {
                    itr = itr->left_child;
                    if (itr->left_child != nil) itr = find_highest_child(itr->right_child);
                } else if (!parent) {
                    itr = end;
                } else if (parent->right_child == itr) {
                    itr = itr->parent;
                } else if (parent->left_child == itr ) {
                    Node *lower_volume_parent = find_lower_volume_parent(parent);
                    if (lower_volume_parent) itr = lower_volume_parent;
                    else itr = end;
                }
                current_node_iteration = itr->number_of_similar;
            }
        }
        return *this;
    }

    template <typename Key, typename Value>
    bool sorted_tree<Key, Value>::Iterator::operator==(const Iterator &other) {
        return this->itr == other.itr && this->current_node_iteration == other.current_node_iteration;
    }

    template <typename Key, typename Value>
    bool sorted_tree<Key, Value>::Iterator::operator!=(const Iterator &other) {
        return this->itr != other.itr || this->current_node_iteration != other.current_node_iteration;
    }

    template <typename Key, typename Value>
    typename sorted_tree<Key, Value>::Node *sorted_tree<Key, Value>::Iterator::find_higher_volume_parent(Node *node) {
        Node *current_node = node->parent;
        while (current_node && current_node->key < node->key) current_node = current_node->parent;
        return current_node;
    }

    template <typename Key, typename Value>
    typename sorted_tree<Key, Value>::Node *sorted_tree<Key, Value>::Iterator::find_lower_volume_parent(Node *node) {
        Node *current_node = node->parent;
        while (current_node && current_node->key > node->key) current_node = current_node->parent;
        return current_node;
    }

}