#include <gtest/gtest.h>

#include "queue"
#include <list>

#include "./test_list.cpp"
#include "./test_queue.cpp"


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}