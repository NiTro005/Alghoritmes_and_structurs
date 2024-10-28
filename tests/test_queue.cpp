// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include "../lib_dmassive/archive.h"
#include "../lib_queue/queue.h"

TEST(TQueueTest, ConstructorAndDestructor) {
    TQueue<int> queue(10);
    EXPECT_EQ(queue.size(), 10);
    EXPECT_TRUE(queue.IsEmpty());
    EXPECT_FALSE(queue.IsFull());
}

TEST(TQueueTest, Push) {
    TQueue<int> queue(3);
    queue.push(1);
    queue.push(2);
    queue.push(3);
    EXPECT_FALSE(queue.IsEmpty());
    EXPECT_TRUE(queue.IsFull());
    EXPECT_EQ(queue.top(), 1);
}

TEST(TQueueTest, Pop) {
    TQueue<int> queue(3);
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.pop();
    EXPECT_EQ(queue.top(), 2);
    queue.pop();
    EXPECT_EQ(queue.top(), 3);
    queue.pop();
    EXPECT_TRUE(queue.IsEmpty());
}

TEST(TQueueTest, PushOverflow) {
    TQueue<int> queue(2);
    queue.push(1);
    queue.push(2);
    EXPECT_THROW(queue.push(3), std::out_of_range);
}

TEST(TQueueTest, PopEmpty) {
    TQueue<int> queue(2);
    EXPECT_THROW(queue.pop(), std::out_of_range);
}

TEST(TQueueTest, TopEmpty) {
    TQueue<int> queue(2);
    EXPECT_THROW(queue.top(), std::out_of_range);
}

TEST(TQueueTest, Overflow) {
    TQueue<int> queue(5);
    queue.push(1);
    queue.push(2);
    queue.push(1);
    queue.push(2);
    queue.push(1);
    queue.pop();
    ASSERT_NO_THROW(queue.push(1));
}
