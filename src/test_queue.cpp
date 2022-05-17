#include "./s21_queue.h"

int main() {
    s21::queue<int> A;
    A.push(3);
    A.push(5);
    A.push(9);
    s21::queue<int> B;
    B.push(17);
    B.push(19);
    B.push(24);
    A.swap(B);

    return 0;
}
