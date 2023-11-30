#include <gtest/gtest.h>
#include <cassert>
#include <iostream>
#include <mutex>
#include <thread>
#include "../include/synchronized_queue.h"

using namespace efficient;
using namespace std;

auto DOUBLE_FUNC = [](int32_t&value) { value *= 2; };
auto decrementFunc = [](int32_t& value) { --value; };

auto THREADS_NUM = 10;
auto THREADS_ACTIVE = vector<bool>(THREADS_NUM, false); 

TEST(SynchronizedBoundedQueueTest, MultipleThreadsTest) {
    SynchronizedBoundedQueue<int, mutex> queue;
    vector<thread> threads;

    for (int threadIndex = 0; threadIndex < THREADS_NUM; ++threadIndex) {
        // Use a lambda to define the operations performed on the same
        // queue by each thread separately
        auto playWithQueue = [&queue] (int threadIndex) {
            THREADS_ACTIVE[threadIndex] = true;
            for (int queueIndex = 0; queueIndex < 10000; ++queueIndex) {
                // Perform a few queue operations
                queue.enqueue(queueIndex);
                queue.enqueue(2*queueIndex);
                queue.dequeue();
            }
            THREADS_ACTIVE[threadIndex] = false;
        };
        // Setup each thread to execute the function that performs the queue operations
        threads.push_back(thread(playWithQueue, threadIndex));
    }

    for (int threadIndex = 0; threadIndex < THREADS_NUM; ++threadIndex) {
        threads[threadIndex].join();
    }

    // Wait until all threads have completed
    for (int threadIndex = 0; threadIndex < THREADS_NUM; ++threadIndex) {
        EXPECT_FALSE(THREADS_ACTIVE[threadIndex]);
    }

    auto elements = queue.clone();
    queue(DOUBLE_FUNC)(decrementFunc);
    EXPECT_EQ(queue.size(), elements.size());

    auto index = 0;
    for(auto element : elements) {
        auto expectedValue = 2 * element - 1;
        EXPECT_EQ(expectedValue, queue[index]);
        ++index;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}