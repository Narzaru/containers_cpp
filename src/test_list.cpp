#include "./s21_list.h"

int main()
{
    s21::list<int> tmp(10);
    // tmp.push_back(13);
    // // tmp.print_cont();
    // tmp.push_front(31);
    // tmp.print_cont();



    // std::cout << "=========================" << std::endl;
    // std::cout << *ptr << std::endl;
    
    s21::list<int> s21list{777, 5};
    s21::list<int> s21list2{566, 123, 123, 5, 6, 7};
    
    s21::list<int>::ListIterator ptr_first = s21list2.begin();
    ptr_first++;
    ptr_first++;

    s21list2.erase(ptr_first);
    // ptr_first++;
    // s21::list<int>::ListIterator ptr_back = s21list2.end();
    // // s21list.swap(s21list2);
    // s21list.merge(s21list2);
    // s21list.sort();
    // s21list.unique();
    // ptr_first.swap_elements(ptr_back);
    std::cout << "=========================" << std::endl;
    std::cout << *ptr_first << std::endl;
    ptr_first--;
    std::cout << *ptr_first << std::endl;
    ptr_first--;
    std::cout << *ptr_first << std::endl;
    // std::list<int> stdlist{44, 55};
    // s21::list<int>::ListIterator s21it= s21list.begin();
    // s21it = s21list.begin();
    // std::list<int>::iterator stdit = stdlist.begin();
    // s21list.insert(s21it, 77);
    // stdlist.insert(stdit, 77);
    // ASSERT_EQ(s21list.front(), stdlist.front());
    // ++s21it;
    // s21list.insert(s21it, 99);
    // s21list.erase(s21it);
    // ASSERT_EQ(s21list.size(), 3);

    // s21::list<int>::ListIterator ptr = tmp.begin();
    // std::cout << "=========================" << std::endl;
    // int i = *(++ptr);
    // // std::cout << i << std::endl; 
    // // s21::list<int>::ListIterator ptr_2 = ptr;
    // // // i = *ptr;
    // std::cout << i << std::endl;
    // i = *ptr;
    // std::cout << i << std::endl;

    // std::cout << i "- value";
    // std::cout << "=========================" << std::endl;
    // std::cout << *ptr << std::endl;B
    // ptr++;
    // std::cout << *ptr << std::endl;c
    // --ptr;
    // std::cout << *ptr << std::endl;
    
    // std::cout << *ptr << std::endl;
    return 0;
}
