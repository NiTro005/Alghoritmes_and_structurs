// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include <string>
#include "../lib_RB_tree/rb_tree.h"

TEST(RBTreeTest, InsertIntoEmptyTree) {
    RBTree<int> tree;
    tree.insert(10);

    EXPECT_TRUE(tree.validate());
    EXPECT_FALSE(tree.isEmpty());
}

TEST(RBTreeTest, InsertMultipleElements) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);

    EXPECT_TRUE(tree.validate());
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(20));
    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(15));
    EXPECT_TRUE(tree.contains(25));
}

TEST(RBTreeTest, InsertDuplicateThrowsException) {
    RBTree<int> tree;
    tree.insert(10);

    EXPECT_THROW(tree.insert(10), std::logic_error);
    EXPECT_TRUE(tree.validate());
}

TEST(RBTreeTest, InsertWithRebalance) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    EXPECT_TRUE(tree.validate());
}

TEST(RBTreeTest, MassInsertion) {
    RBTree<int> tree;
    for (int i = 1; i <= 100; ++i) {
        tree.insert(i);
        EXPECT_TRUE(tree.validate());
    }

    for (int i = 1; i <= 100; ++i) {
        EXPECT_TRUE(tree.contains(i));
    }
}

TEST(RBTreeTest, InsertInReverseOrder) {
    RBTree<int> tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);

    EXPECT_TRUE(tree.validate());
}

TEST(RBTreeTest, InsertRandomValues) {
    RBTree<int> tree;
    std::vector<int> values = { 5, 3, 7, 2, 4, 6, 8, 1, 9, 0 };

    for (int val : values) {
        tree.insert(val);
        EXPECT_TRUE(tree.validate());
    }

    for (int val : values) {
        EXPECT_TRUE(tree.contains(val));
    }
}

TEST(RBTreeTest, InsertNegativeNumbers) {
    RBTree<int> tree;
    tree.insert(-10);
    tree.insert(-20);
    tree.insert(-5);

    EXPECT_TRUE(tree.validate());
    EXPECT_TRUE(tree.contains(-10));
    EXPECT_TRUE(tree.contains(-20));
    EXPECT_TRUE(tree.contains(-5));
}

TEST(RBTreeTest, InsertMixedNumbers) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(-5);
    tree.insert(0);
    tree.insert(20);
    tree.insert(-15);

    EXPECT_TRUE(tree.validate());
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(-5));
    EXPECT_TRUE(tree.contains(0));
    EXPECT_TRUE(tree.contains(20));
    EXPECT_TRUE(tree.contains(-15));
}
