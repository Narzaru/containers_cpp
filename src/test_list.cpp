#include "./s21_list.h"

int main()
{
    s21::list<int> tmp(10);
    tmp.push_back(13);
    // tmp.print_cont();
    tmp.push_front(31);
    tmp.print_cont();

    s21::list<int> ptr = tmp;

    ptr = tmp;
    
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
