namespace s21 {
    template <typename Key>
    void set<Key>::Node::free_node() {
        parent = nullptr;
        left_child = nullptr;
        right_child = nullptr;
        key = 0;
        value = 0;
        color = RED;
    }

    template <typename Key>
    void set<Key>::Node::free_node_recursive(Node* node, Node *nil) {
        node->parent = nullptr;
        if (node->left_child != nil) free_node_recursive(node->left_child, nil);
        if (node->right_child != nil) free_node_recursive(node->right_child, nil);
        node->left_child = nullptr;
        node->right_child = nullptr;
        node->key = 0;
        node->value = 0;
        node->color = RED;
        delete node;
    }

    template<typename Key>
    set<Key>::set() : size_(0) {
        nil = new Node();
        root_ = nullptr;
        max_size_ = std::numeric_limits<std::size_t>::max() / sizeof(Key);
    }

    template <typename Key>
    void set<Key>::clear() {
        if (root_) {
            root_->free_node_recursive(root_, nil);
        }
        delete nil;
    }

    template<typename Key>
    typename set<Key>::Node *set<Key>::SetIterator::find_lowest_child(Node *node) {
        Node *current_child = node;
        if (node && node != nil && node->left_child != nil) {
            current_child = node->left_child;
            while (current_child->left_child != nil) {
                current_child = current_child->left_child;
            }
        }
        return current_child;
    }

    template<typename Key>
    typename set<Key>::Node *set<Key>::SetIterator::find_highest_child(Node *node) {
        Node *current_child = node;
        if (node && node != nil && node->right_child != nil) {
            current_child = node->right_child;
            while (current_child->right_child != nil) {
                current_child = current_child->right_child;
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
        iterator iter(*this);
        iter.itr = iter.end;
        return iter;
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
        // Node *new_node = new Node();
        if (root_ == nullptr) {
            root_ = new Node(value, BLACK, nullptr, nil, nil);;
            result.first = this->begin();
            result.second = true;
            size_++;
        } else {
            Node *current_node = find_node_to_insert(value);
            if (current_node->value == value) {
                result.second = false;
            } else {
                Node *new_node = new Node(value, RED, current_node, nil, nil);
                if (current_node->value > value) {
                    current_node->left_child = new_node;
                    current_node = current_node->left_child;
                } else {
                    current_node->right_child = new_node;
                    current_node = current_node->right_child;
                }
                result.second = true;
                size_++;
                fix_up_insert(current_node);
            }
            result.first = this->begin();
            iterator *current_iterator = &result.first;
            current_iterator->itr = current_node;
        }
        return result;
    }

    template<typename Key>
    void set<Key>::erase(iterator pos) {
        if (pos.itr != pos.end) {
            erase_existing(pos);
            size_--;
        }
    }

    template<typename Key>
    void set<Key>::erase_existing(iterator pos) {
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

    template<typename Key>
    typename set<Key>::Node *set<Key>::find_node_to_insert(const value_type& value) {
        Node *current_node = root_;
        while (current_node->value > value && current_node->left_child != nil || current_node->value < value && current_node->right_child != nil) {
            if (current_node->value > value) current_node = current_node->left_child;
            if (current_node->value < value) current_node = current_node->right_child;
        }
        return current_node;
    }

    template<typename Key>
    void set<Key>::rotate_left(Node *node) {
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

    template<typename Key>
    void set<Key>::rotate_right(Node *node) {
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
    
    
    template<typename Key>
    void set<Key>::fix_up_insert(Node *node) {
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
                    gparent->color = RED;
                    parent->color = BLACK;
                    break;
                }
            }
        }
        root_->color = BLACK;        
    }

    template<typename Key>
    void set<Key>::fix_up_erase(Node *node, Node *parent) {
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

    // ITERATOR

    template <typename Key>
    void set<Key>::SetIterator::nullify_iterator_properties() {
        first = nullptr;
        end = nullptr;
        itr = nullptr;
        nil = nullptr;
    }

    template <typename Key>
    void set<Key>::SetIterator::free_iterator() {
        if (end != nil) delete end;
        nullify_iterator_properties();
    }


    template <typename Key>
    Key& set<Key>::SetIterator::operator* () const {
        if (itr == nullptr) {
            // бросить исключение
        }
        return itr->value;
    }

    template <typename Key>
    typename set<Key>::SetIterator set<Key>::SetIterator::operator++() {
        Node *parent = itr->parent;
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
        return *this;
    }


    template <typename Key>
    typename set<Key>::SetIterator set<Key>::SetIterator::operator--() {
        Node *parent = itr->parent;
        if (itr == end) {
            itr = itr->parent;
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
        }
        return *this;
    }

    template <typename Key>
    bool set<Key>::SetIterator::operator==(const SetIterator &other) {
        return this->itr == other.itr;
    }

    template <typename Key>
    bool set<Key>::SetIterator::operator!=(const SetIterator &other) {
        return this->itr != other.itr;
    }

    template<typename Key>
    typename set<Key>::Node *set<Key>::SetIterator::find_higher_volume_parent(Node *node) {
        Node *current_node = node->parent;
        while (current_node && current_node->value < node->value) current_node = current_node->parent;
        return current_node;
    }

    template<typename Key>
    typename set<Key>::Node *set<Key>::SetIterator::find_lower_volume_parent(Node *node) {
        Node *current_node = node->parent;
        while (current_node && current_node->value > node->value) current_node = current_node->parent;
        return current_node;
    }

    template<typename Key>
    typename set<Key>::iterator set<Key>::find(const Key& key) {
        iterator result = this->begin();
        if (root_ != nil) {
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

    template<typename Key>
    bool set<Key>::contains(const Key& key) {
        iterator current = find(key);
        return current.itr != current.end;
    }

}