#include <gtest/gtest.h>

// !TODO(bgreydon) delete this includes
#include <vector>
#include <iostream>

class A {
  public:
  A() : A(0){}
  explicit A(int a) : a(a){}
  int getA() {return a;}
  private:
  int a;
};

int main(int argc, char *argv[]) {
  std::vector<int> var({0,0,0,0,0});
  std::cout << "size: " << var.size() << std::endl;
  std::cout << "max size: " << var.max_size() << std::endl;
  std::cout << "capacity: " << var.capacity() << std::endl;

  std::cout << "base" << std::endl;
  for (int i = 0; i < var.size(); ++i) {
    std::cout << var[i];
  }
  std::cout << std::endl;

  var.reserve(100);

  std::cout << "inserted" << std::endl;
  for (int i = 0; i < var.size(); ++i) {
    std::cout << var[i];
  }
  std::cout << std::endl;

  std::cout << "size: " << var.size() << std::endl;
  std::cout << "max size: " << var.max_size() << std::endl;
  std::cout << "capacity: " << var.capacity() << std::endl;
  return 0;
}
