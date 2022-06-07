#ifndef SRC_S21_SET_S21_SET_H_
#define SRC_S21_SET_S21_SET_H_

#pragma once
#include "../s21_sorted_tree/s21_sorted_tree.h"

namespace s21 {
template <typename Key, typename Value = int>
class set : public sorted_tree<Key, Value> {
 public:
  using value_type = Key;
  using iterator = typename sorted_tree<Key, Value>::Iterator;
  using const_iterator = typename sorted_tree<Key, Value>::ConstIterator;

  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  set& operator=(const set& s);
  set& operator=(set&& s);
  ~set();

  std::pair<iterator, bool> insert(const value_type& value);
  void merge(set& other);  // NOLINT(*)

  using sorted_tree<Key, Value>::find;

  template <typename... Args>
  inline std::pair<iterator, bool> emplace(Args&&... args) {
    return insert(value_type(std::forward<Args>(args)...));
  }
};
}  // namespace s21

#include "s21_set.inc"

#endif  // SRC_S21_SET_S21_SET_H_
