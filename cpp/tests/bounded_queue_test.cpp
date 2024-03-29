#include <gtest/gtest.h>
#include <iostream>
#include "../include/bounded_queue.h"

using namespace efficient;
using namespace std;

/** Function doubles a given value*/
auto DOUBLE_FUNC = [](int32_t& value) { value = 2 * value; };

/** Function decrements by 1 the given value*/
auto decrementFunc = [](int32_t& value) { --value; };

TEST(BoundedQueueTest, PushTest) {
    bounded_queue<int> queue;
    int values[] = {1, -2, 3, -4, 5, 6, 0};
    for_each (begin(values), end(values), [&queue](int value) {
        queue.push(value);
    });

    EXPECT_EQ(queue.size(), size(values));

    size_t index = 0;
    for_each (begin(values), end(values), [&queue, &index](int value) {
        EXPECT_EQ(queue[index], value);
        ++index;
    });
}

TEST(BoundedQueueTest, PopTest) {
    bounded_queue<int> queue;
    int values[] = {1, -2, 3, -4, 5, 6, 0};
    for_each (begin(values), end(values), [&queue](int value) {
        queue.push(value);
    });

    for_each (begin(values), end(values), [&queue](int value) {
        auto poppedValue = queue.pop();
        EXPECT_EQ(poppedValue, value);
    });
    EXPECT_EQ(queue.size(), 0);
}

TEST(BoundedQueueTest, ClearTest) {
    bounded_queue<int> queue;
    int values[] = {1, -2, 3, -4, 5, 6, 0};
    for_each (begin(values), end(values), [&queue](int value) {
        queue.push(value);
    });

    queue.clear();
    EXPECT_EQ(queue.size(), 0);
}

TEST(BoundedQueueTest, PopEmptyQueueTest) {
    bounded_queue<int> queue;
    ASSERT_THROW(queue.pop(), logic_error);
}

TEST(BoundedQueueTest, PushTooManyTest) {
    int values[] = {1, -2, 3, -4, 5, 6, 0};
    bounded_queue<int> queue(size(values));

    for_each (begin(values), end(values), [&queue](int value) {
        queue.push(value);
    });

    // Push 1 more beyond the queue max size
    ASSERT_THROW(queue.push(0), logic_error);
}


TEST(BoundedQueueTest, OutOfBoundsIndexTest) {
    int values[] = {1, -2, 3, -4, 5, 6, 0};
    bounded_queue<int> queue;

    for_each (begin(values), end(values), [&queue](int value) {
        queue.push(value);
    });

    ASSERT_THROW(queue[size(values)], logic_error);
}

TEST(BoundedQueueTest, ValidIndexTest) {
    int values[] = {1, -2, 3, -4, 5, 6, 0};
    bounded_queue<int> queue;

    for_each (begin(values), end(values), [&queue](int value) {
        queue.push(value);
    });

    auto index = 3;
    EXPECT_EQ(queue[index], values[index]);
}

TEST(BoundedQueueTest, AppplyChainedFunctionsTest) {
    int values[] = {1, -2, 3, -4, 5, 6, 0};
    bounded_queue<int> queue;

    for_each (begin(values), end(values), [&queue](int value) {
        queue.push(value);
    });

    // Apply a series of functions to each element in the queue.
    queue(DOUBLE_FUNC)(decrementFunc);

    EXPECT_EQ(queue.size(), size(values));

    auto index = 0;
    for_each (begin(values), end(values), [&queue, &index](int value) {
        EXPECT_EQ(queue[index], 2* value - 1);
        ++index;
    });
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
