// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include "../lib_heap/heap.h"

TEST(HeapTest, InsertIntoEmptyHeap) {
    Heap<int> heap(5, MAX);
    heap.insert(10);
    EXPECT_EQ(heap.top(), 10);
    EXPECT_FALSE(heap.is_empty());
}

TEST(HeapTest, InsertSmallerElementInMaxHeap) {
    Heap<int> heap(5, MAX);
    heap.insert(10);
    heap.insert(5);
    EXPECT_EQ(heap.top(), 10);
}

TEST(HeapTest, InsertLargerElementInMaxHeap) {
    Heap<int> heap(5, MAX);
    heap.insert(5);
    heap.insert(10);
    EXPECT_EQ(heap.top(), 10);
}

TEST(HeapTest, InsertEqualElements) {
    Heap<int> heap(5, MAX);
    heap.insert(5);
    heap.insert(5);
    EXPECT_EQ(heap.top(), 5);
}


TEST(HeapTest, InsertInMinHeap) {
    Heap<int> heap(5, MIN);
    heap.insert(5);
    heap.insert(3);
    heap.insert(7);
    EXPECT_EQ(heap.top(), 3);
}

TEST(HeapTest, InsertMultipleElementsRandomOrder) {
    Heap<int> heap(10, MAX);
    heap.insert(3);
    heap.insert(1);
    heap.insert(4);
    heap.insert(1);
    heap.insert(5);
    heap.insert(9);
    EXPECT_EQ(heap.top(), 9);
}

//TEST(HeapTest, InsertAfterRemove) {
//    Heap<int> heap(5, MAX);
//    heap.insert(5);
//    heap.insert(3);
//    heap.remove();
//    heap.insert(4);
//    EXPECT_EQ(heap.top(), 4);
//}