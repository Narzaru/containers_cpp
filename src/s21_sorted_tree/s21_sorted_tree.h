#ifndef SRC_S21_SORTED_TREE_H_
#define SRC_S21_SORTED_TREE_H_

#pragma once
#include <cstddef>

typedef enum {
    RED,
    BLACK
} node_color;

namespace s21 {
template <typename Key, typename Value>
class sorted_tree {
 public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = std::size_t;

    void clear();

    sorted_tree();
    sorted_tree(const sorted_tree<Key, Value> &other);
    sorted_tree(sorted_tree<Key, Value> &&other);
    sorted_tree& operator=(const sorted_tree<Key, Value>& other);
    sorted_tree& operator=(sorted_tree<Key, Value>&& other);

    ~sorted_tree() {
        free_sorted_tree();
    }

    bool empty() const;
    size_type size() const;
    size_type max_size() const;

    class Node {
     public:
        Key key;
        Value value;
        node_color color;
        Node *parent;
        Node *left_child;
        Node *right_child;

        int number_of_similar;

        explicit Node(Key d_key = Key(), Value d_value = Value(), node_color d_color = BLACK,
            Node *d_parent = nullptr, Node *d_left_child = nullptr, Node *d_right_child = nullptr)
            : key(d_key), value(d_value), color(d_color), parent(d_parent),
            left_child(d_left_child), right_child(d_right_child) {
            number_of_similar = 1;
        }
        ~Node() {
            free_node();
        }
        void free_node();
        void free_node_recursive(Node*, Node*);
    };

    class Iterator {
     public:
        Node *first;
        Node *end;
        Node *itr;
        Node *nil;
        int current_node_iteration;

        Node *find_lowest_child(Node *node);
        Node *find_highest_child(Node *node);

        Iterator() {
            nullify_iterator_properties();
        }

        ~Iterator() {
            free_iterator();
        }

        explicit Iterator(const sorted_tree& other) {
            current_node_iteration = 1;
            nil = other.nil;
            first = find_lowest_child(other.root_);
            if (!first) first = nil;
            Node *highest_value = find_highest_child(other.root_);
            end = nil;
            if (highest_value) nil->key = highest_value->key;
            if (nil) nil->parent = highest_value;
            itr = first;
        }

        virtual value_type operator*() const;
        Iterator operator++();
        Iterator operator--();
        bool operator==(const Iterator &other);
        bool operator!=(const Iterator &other);

        Node *find_higher_volume_parent(Node *node);
        Node *find_lower_volume_parent(Node *node);
        void free_iterator();
        void nullify_iterator_properties();
    };
    using iterator = Iterator;
    iterator begin();
    iterator end();

    class ConstIterator : public Iterator {
     public:
        ConstIterator() {
        }

        ~ConstIterator() {
        }

        explicit ConstIterator(const sorted_tree<Key, Value>& other) : Iterator(other) {
        }
    };
    using const_iterator = ConstIterator;
    const_iterator cbegin() const;
    const_iterator cend() const;

    void erase(iterator pos);
    void swap(sorted_tree<Key, Value>& other);
    // void merge(sorted_tree<Key, Value>& other);

    bool contains(const Key& key);

 private:
    size_type size_;
    size_type max_size_;
    Node *root_;
    void reset();
    void free_sorted_tree();
    void erase_existing(iterator pos);
    void set_initial_properties();
    Node *find_node_to_insert(const value_type &value);
    void rotate_left(Node *node);
    void rotate_right(Node *node);
    void fix_up_insert(Node *node);
    void fix_up_erase(Node *node, Node *parent);

 protected:
    Node *nil;
    iterator insert_pair(const value_type& value);
    iterator find(const Key& key);
    iterator lower_bound(const Key& key);
    iterator upper_bound(const Key& key);
    std::pair<iterator, iterator> equal_range(const Key &key);
};
}  // namespace s21

#include "s21_sorted_tree.inc"

#endif  // SRC_S21_SORTED_TREE_H_
