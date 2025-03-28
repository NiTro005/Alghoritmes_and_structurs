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

TEST(HeapTest, InsertAfterRemove) {
    Heap<int> heap(5, MAX);
    heap.insert(5);
    heap.insert(3);
    heap.remove();
    heap.insert(4);
    EXPECT_EQ(heap.top(), 4);
}

TEST(HeapTest, RemoveMaintainsMaxHeapProperty) {
    Heap<int> heap(5, MAX);
    heap.insert(3);
    heap.insert(1);
    heap.insert(4);
    heap.insert(1);
    heap.insert(5);

    EXPECT_EQ(heap.remove(), 5);
    EXPECT_EQ(heap.remove(), 4);
    EXPECT_EQ(heap.remove(), 3);
    EXPECT_EQ(heap.remove(), 1);
    EXPECT_EQ(heap.remove(), 1);
}

TEST(HeapTest, RemoveMaintainsMinHeapProperty) {
    Heap<int> heap(5, MIN);
    heap.insert(3);
    heap.insert(1);
    heap.insert(4);
    heap.insert(1);
    heap.insert(5);

    EXPECT_EQ(heap.remove(), 1);
    EXPECT_EQ(heap.remove(), 1);
    EXPECT_EQ(heap.remove(), 3);
    EXPECT_EQ(heap.remove(), 4);
    EXPECT_EQ(heap.remove(), 5);
}

TEST(HeapTest, RemoveFromEmptyThrows) {
    Heap<int> heap(2, MAX);
    EXPECT_THROW(heap.remove(), std::logic_error);
}

TEST(HeapTest, ComplexOperationSequence) {
    Heap<int> heap(10, MAX);

    heap.insert(5);
    heap.insert(10);
    heap.insert(3);
    EXPECT_EQ(heap.remove(), 10);

    heap.insert(7);
    heap.insert(1);
    EXPECT_EQ(heap.remove(), 7);
    EXPECT_EQ(heap.remove(), 5);

    heap.insert(12);
    EXPECT_EQ(heap.remove(), 12);
    EXPECT_EQ(heap.remove(), 3);
    EXPECT_EQ(heap.remove(), 1);
}

//TEST(HeapTest, HeapifyAfterConstruction) {
//    // Проверяем корректность работы конструктора с массивом
//    int data[] = { 3, 1, 4, 1, 5, 9 };
//    Heap<int> heap(6, data, MAX);
//
//    EXPECT_EQ(heap.remove(), 9);
//    EXPECT_EQ(heap.remove(), 5);
//    EXPECT_EQ(heap.remove(), 4);
//    EXPECT_EQ(heap.remove(), 3);
//    EXPECT_EQ(heap.remove(), 1);
//    EXPECT_EQ(heap.remove(), 1);
//}
