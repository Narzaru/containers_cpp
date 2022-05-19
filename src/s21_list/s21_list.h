#ifndef SRC_S21_LIST_S21_LIST_H_
#define SRC_S21_LIST_S21_LIST_H_
#include <cstddef>
#include <initializer_list>

namespace s21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  void print_cont();
  bool empty();
  size_t size();
  size_t max_size();
  void clear();
  void push_back(T data);
  void pop_back();
  void push_front(T data);
  void pop_front();
  void reverse();
  void swap(list& other);
  void unique();
  void sort();
  void merge(list& other);

  T& front() const;
  T& back() const;

  list& operator=(list& other);

  list<T>();
  list<T>(size_t n);
  list<T>(std::initializer_list<T> const& items);
  list<T>(list&& l);
  list(const list& l);

  ~list() { clear(); }

  class listNode {
   public:
    listNode* pNext;
    listNode* pPrev;

    explicit listNode(T data = T(), listNode* pNext = nullptr,
                      listNode* pPrev = nullptr) {
      this->data = data;
      this->pNext = pNext;
      this->pPrev = pPrev;
    }

    ~listNode() { free_memory(); }
    T data;
    void free_memory();
  };
  typedef list<T>::listNode node;

  class ListIterator {
   public:
    node* first;
    node* end;
    node* itr;

    ListIterator() {
      first = nullptr;
      end = nullptr;
      itr = nullptr;
    }
    explicit ListIterator(const list<T>& other) {
      first = other.head_;
      end = other.back_;
      itr = other.head_;
    }
    ~ListIterator() { free_iterator(); }
    void swap_elements(ListIterator pos);
    void free_iterator();
    T& operator*() const;
    ListIterator operator++();
    ListIterator operator++(int);
    ListIterator operator--();
    ListIterator operator--(int);
    bool operator==(const ListIterator& other);
    bool operator!=(const ListIterator& other);
  };
  using iterator = typename list<T>::ListIterator;

  iterator begin();
  iterator end();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);

  class ListConstIterator {
   public:
    node* first;
    node* end;
    node* itr;

    ListConstIterator() {
      first = nullptr;
      end = nullptr;
      itr = nullptr;
    }
    explicit ListConstIterator(const list<T>& other) {
      first = other.head_;
      end = other.back_;
      itr = other.head_;
    }
    ~ListConstIterator() { free_iterator(); }

    void free_iterator();
    T& operator*() const;
    ListConstIterator operator++();
    ListConstIterator operator++(int);
    ListConstIterator operator--();
    ListConstIterator operator--(int);
    bool operator==(const ListConstIterator& other);
    bool operator!=(const ListConstIterator& other);
  };
  using const_iterator = typename list<T>::ListConstIterator;

  const_iterator cbegin() const;
  const_iterator cend() const;
  void splice(const_iterator pos, list& other);

 private:
  size_t size_;  // максимальный размер
  node* head_;
  node* back_;  // реализовать присваивание
  void last_node();
};

}  // namespace s21
#include "s21_list.inc"

#endif  // SRC_S21_LIST_S21_LIST_H_
