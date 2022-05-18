#include "./s21_queue.h"
#include "./s21_list.h"

int main() {
    s21::list<int> A = {99, 2, 3, 4};
    int tmp = A.front();
    // s21::list<int> C(A);
    s21::queue<double> B;
    B.push(17.33);
    B.push(19);
    B.push(24);
    double Ad = B.front();

    double C = B.back();

    // A = std::moveB;

    return 0;
}
