#pragma once
#include <cstddef>

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
        void free_set();
        

        set<Key>();
        set<Key>(std::initializer_list<Key> const &items);
        set<Key>(const set<Key> &s);
        set<Key>(set<Key> &&s);
        set<Key> & operator=(const set<Key>& s);
        set<Key> & operator=(set<Key>&& s);

        ~set() {
            free_set();
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
            void free_node_recursive(Node*, Node*);
        };

        Node *find_node_to_insert(const value_type& value);
        void rotate_left(Node *node);
        void rotate_right(Node *node);
        void fix_up_insert(Node *node);
        void fix_up_erase(Node *node, Node *parent);

        class SetIterator {
         public:
            Node *first;
            Node *end;
            Node *itr;
            Node *nil;

            Node *find_lowest_child(Node *node);
            Node *find_highest_child(Node *node);

            SetIterator() {
                nullify_iterator_properties();
            };

            ~SetIterator() {
                free_iterator();
            }

            explicit SetIterator(const set<Key>& other) {
                nil = other.nil;
                first = find_lowest_child(other.root_);
                Node *highest_value = find_highest_child(other.root_);
                end = nil;
                if (highest_value) nil->value = highest_value->value;
                if (nil) nil->parent = highest_value;
                itr = first;
            }

            Key& operator*() const;
            SetIterator operator++();
            SetIterator operator--();
            bool operator==(const SetIterator &other);
            bool operator!=(const SetIterator &other);

            Node *find_higher_volume_parent(Node *node);
            Node *find_lower_volume_parent(Node *node);
            void free_iterator();
            void nullify_iterator_properties();
        };
        using iterator = SetIterator;
        iterator begin();
        iterator end();

        class SetConstIterator : public SetIterator {
         public:
            SetConstIterator() {
            };

            ~SetConstIterator() {
            }

            explicit SetConstIterator(const set<Key>& other) : SetIterator(other) {
            }
        };
        using const_iterator = SetConstIterator;
        const_iterator cbegin() const;
        const_iterator cend() const;


        std::pair<iterator, bool> insert(const value_type& value);
        void erase(iterator pos);
        void erase_existing(iterator pos);
        void swap(set<Key>& other);
        void merge(set<Key>& other);

        iterator find(const Key& key);
        bool contains(const Key& key);
        

     private:
        size_type size_;
        size_type max_size_;
        Node *root_;
        Node *nil;
        void set_initial_properties();
        void reset();

    };
}

#include "s21_set.inl"
