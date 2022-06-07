#include <gtest/gtest.h>

#include "s21_containers.h"

namespace map_constructors_suite {
TEST(constructors, empty_constructor) {
  s21::map<int, double> map;
  std::map<int, double> origin;
  ASSERT_EQ(map.size(), origin.size());
}

TEST(constructors, initializer_list) {
  s21::map<int, double> map{{1, 1}, {2, 2}, {3, 3}};
  std::map<int, double> origin{{1, 1}, {2, 2}, {3, 3}};
  ASSERT_EQ(map.size(), origin.size());
  auto it_origin = origin.begin();
  for (auto it = map.begin(); it != map.end() && it_origin != origin.end();
       ++it, ++it_origin) {
    ASSERT_EQ((*it).first, (*it_origin).first);
    ASSERT_EQ((*it).second, (*it_origin).second);
  }
}
}  // namespace map_constructors_suite

namespace map_insert_suite {
TEST(insert, insert_several_pairs) {
  s21::map<int, std::string> map;
  std::map<int, std::string> origin{{1, "One_first"}, {2, "Two"}, {0, "Zero"}};
  map.insert(std::make_pair(1, "One_first"));
  map.insert(std::make_pair(2, "Two"));
  map.insert(std::make_pair(1, "One_second"));
  map.insert(std::make_pair(0, "Zero"));
  map.insert(std::make_pair(1, "One_third"));
  ASSERT_EQ(map.size(), origin.size());
  auto it_origin = origin.begin();
  for (auto it = map.begin(); it != map.end() && it_origin != origin.end();
       ++it, ++it_origin) {
    ASSERT_EQ((*it).first, (*it_origin).first);
    ASSERT_EQ((*it).second, (*it_origin).second);
  }
}

TEST(insert, insert_several_keys_values) {
  s21::map<int, std::string> map;
  std::map<int, std::string> origin{{1, "One_first"}, {2, "Two"}, {0, "Zero"}};
  map.insert(1, "One_first");
  map.insert(2, "Two");
  map.insert(1, "One_second");
  map.insert(0, "Zero");
  map.insert(1, "One_third");
  ASSERT_EQ(map.size(), 3);
  ASSERT_EQ(map.size(), origin.size());
  auto it_origin = origin.begin();
  for (auto it = map.begin(); it != map.end() && it_origin != origin.end();
       ++it, ++it_origin) {
    ASSERT_EQ((*it).first, (*it_origin).first);
    ASSERT_EQ((*it).second, (*it_origin).second);
  }
}

TEST(insert, insert_or_assign) {
  s21::map<int, std::string> map;
  std::map<int, std::string> origin{{1, "One_third"}, {2, "Two"}, {0, "Zero"}};
  map.insert_or_assign(1, "One_first");
  map.insert_or_assign(2, "Two");
  map.insert_or_assign(1, "One_second");
  map.insert_or_assign(0, "Zero");
  map.insert_or_assign(1, "One_third");
  ASSERT_EQ(map.size(), 3);
  ASSERT_EQ(map.size(), origin.size());
  auto it_origin = origin.begin();
  for (auto it = map.begin(); it != map.end() && it_origin != origin.end();
       ++it, ++it_origin) {
    ASSERT_EQ((*it).first, (*it_origin).first);
    ASSERT_EQ((*it).second, (*it_origin).second);
  }
}
}  // namespace map_insert_suite

namespace map_erase_suite {
TEST(erase, erase_elements) {
  s21::map<int, std::string> map{{1, "One"}, {2, "Two"}, {3, "Three"}};
  std::map<int, std::string> origin{{1, "One"}, {2, "Two"}, {3, "Three"}};
  ASSERT_EQ(map.size(), 3);
  auto it = map.begin();
  auto it_origin = origin.begin();
  ++it;
  ++it_origin;
  map.erase(it);
  origin.erase(it_origin);
  ASSERT_EQ(map.size(), 2);
  ASSERT_EQ(origin.size(), 2);
  EXPECT_THROW(map.at(2), std::out_of_range);

  it = map.begin();
  it_origin = origin.begin();
  for (; it != map.end() && it_origin != origin.end(); ++it, ++it_origin) {
    ASSERT_EQ((*it).first, (*it_origin).first);
    ASSERT_EQ((*it).second, (*it_origin).second);
  }
  ASSERT_TRUE(it == map.end());
}
}  // namespace map_erase_suite

namespace map_elements_access_suite {
TEST(elements_access, at) {
  s21::map<int, double> map{{1, 1}, {2, 2}, {3, 3}};
  std::map<int, double> origin{{1, 1}, {2, 2}, {3, 3}};
  ASSERT_EQ(map.at(1), origin.at(1));
  ASSERT_EQ(map.at(2), origin.at(2));
  ASSERT_EQ(map.at(3), origin.at(3));
  map.at(1) = 4;
  ASSERT_EQ(map.at(1), 4);
  EXPECT_THROW(map.at(4), std::out_of_range);
}

TEST(elements_access, square_brackets) {
  s21::map<int, double> map{{1, 1}, {2, 2}, {3, 3}};
  std::map<int, double> origin{{1, 1}, {2, 2}, {3, 3}};
  ASSERT_EQ(map[1], origin[1]);
  ASSERT_EQ(map[2], origin[2]);
  ASSERT_EQ(map[3], origin[3]);

  map[1] = 4;
  origin[1] = 4;
  ASSERT_EQ(map[1], origin[1]);
  EXPECT_THROW(map[4], std::out_of_range);
}
}  // namespace map_elements_access_suite

namespace map_additional_functions_suite {
TEST(additional_functions, merge) {
  s21::map<int, double> map1{{1, 1}, {2, 2}, {3, 3}},
      map2{{4, 4}, {5, 5}, {6, 6}};
  std::map<int, double> origin1{{1, 1}, {2, 2}, {3, 3}},
      origin2{{4, 4}, {5, 5}, {6, 6}};
  map1.merge(map2);
  origin1.merge(origin2);
  ASSERT_EQ(map1.size(), origin1.size());
  ASSERT_EQ(map2.size(), origin2.size());
  auto it = map1.begin();
  auto it_origin = origin1.begin();
  for (; it != map1.end() && it_origin != origin1.end(); ++it, ++it_origin) {
    ASSERT_EQ((*it).first, (*it_origin).first);
    ASSERT_EQ((*it).second, (*it_origin).second);
  }
}

TEST(additional_functions, swap) {
  s21::map<int, double> map1{{1, 1}, {2, 2}, {3, 3}},
      map2{{4, 4}, {5, 5}, {6, 6}, {7, 7}};
  std::map<int, double> origin1{{1, 1}, {2, 2}, {3, 3}},
      origin2{{4, 4}, {5, 5}, {6, 6}, {7, 7}};
  map1.swap(map2);
  origin1.swap(origin2);
  ASSERT_EQ(map1.size(), 4);
  ASSERT_EQ(map2.size(), 3);
  ASSERT_EQ(map1.size(), origin1.size());
  ASSERT_EQ(map2.size(), origin2.size());
  ASSERT_EQ(map1[4], origin1[4]);
  ASSERT_EQ(map1[7], origin1[7]);
  ASSERT_EQ(map2[1], origin2[1]);
  EXPECT_THROW(map2[4], std::out_of_range);
}

}  // namespace map_additional_functions_suite

namespace map_iterator_suite {
TEST(iterators, map_iterator) {
  s21::map<int, double> map;
  std::map<int, double> origin{{1, 4}, {2, 5}, {3, 6}};
  map.insert(1, 4);
  map.insert(2, 5);
  map.insert(3, 6);
  auto it = map.begin();
  auto it_origin = origin.begin();
  for (; it != map.end() && it_origin != origin.end(); ++it, ++it_origin) {
    ASSERT_EQ((*it).first, (*it_origin).first);
    ASSERT_EQ((*it).second, (*it_origin).second);
  }
}
}  // namespace map_iterator_suite

namespace map_emplace_suite {
TEST(emplace, insert_using_emplace) {
  s21::map<int, double> map;
  std::map<int, double> origin;
  map.emplace(1, 4);
  map.emplace(2, 5);
  map.emplace(std::pair<int, double>(3, 6));
  origin.emplace(1, 4);
  origin.emplace(2, 5);
  origin.emplace(std::pair<int, double>(3, 6));
  auto it = map.begin();
  auto it_origin = origin.begin();
  for (; it != map.end() && it_origin != origin.end(); ++it, ++it_origin) {
    ASSERT_EQ((*it).first, (*it_origin).first);
    ASSERT_EQ((*it).second, (*it_origin).second);
  }
}
}  // namespace map_emplace_suite
