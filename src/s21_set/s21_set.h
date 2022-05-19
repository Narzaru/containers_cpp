#pragma once
#include <cstddef>
#include <initializer_list>

typedef enum {
    RED,
    BLACK
} node_color;

namespace s21 {
    template <typename Key>
    class set {
     public:
        using key_type = Key;
        using value_type = Key;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = std::size_t;

        void clear();
        

        set<Key>();
        ~set() {
            clear();
        };

        bool empty() const;
        size_type size() const;
        size_type max_size() const;

        class Node {
         public:
            key_type key;
            value_type value;
            node_color color;

            Node *parent;
            Node *left_child;
            Node *right_child;

            Node(value_type value = value_type(), node_color color = BLACK, Node *parent = nullptr, Node *left_child = nullptr, Node *right_child = nullptr) {
                this->key = value;
                this->value = value;
                this->color = color;
                this->parent = parent;
                this->left_child = left_child;
                this->right_child = right_child;
            };
            ~Node() {
                free_node();
            }
            void free_node();
        };

        Node *nil;
        Node *find_node_to_insert(const value_type& value);

        class SetIterator {
         public:
            Node *first;
            Node *end;
            Node *itr;

            Node *find_first(const set<Key>& other);

            SetIterator() {
                free_iterator();
            };

            ~SetIterator() {
                free_iterator();
            }

            explicit SetIterator(const set<Key>& other) {
                first = find_first(other);
                end = other.nil;
                itr = first;
            }

            Key& operator*() const;
            void free_iterator();
        };
        using iterator = SetIterator;
        iterator begin();
        iterator end();

        std::pair<iterator, bool> insert(const value_type& value);

        iterator find(const Key& key);
        bool contains(const Key& key);
        

     private:
        size_type size_;
        size_type max_size_;
        Node *root_;

    };
}

#include "s21_set.inl"
