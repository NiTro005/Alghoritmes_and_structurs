// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include <vector>
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

// Тесты для удаления элементов
TEST(RBTreeTest, RemoveFromEmptyTree) {
    RBTree<int> tree;
    tree.remove(10);
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_TRUE(tree.validate());
}

TEST(RBTreeTest, RemoveRoot) {
    RBTree<int> tree;
    tree.insert(10);
    tree.remove(10);

    EXPECT_TRUE(tree.isEmpty());
    EXPECT_TRUE(tree.validate());
}

TEST(RBTreeTest, RemoveLeafNode) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.remove(5);

    EXPECT_FALSE(tree.contains(5));
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(15));
    EXPECT_TRUE(tree.validate());
}

TEST(RBTreeTest, RemoveNodeWithOneChild) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.remove(5);

    EXPECT_FALSE(tree.contains(5));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(15));
    EXPECT_TRUE(tree.validate());
}

TEST(RBTreeTest, RemoveNodeWithTwoChildren) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.remove(5);

    EXPECT_FALSE(tree.contains(5));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_TRUE(tree.contains(7));
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(15));
    EXPECT_TRUE(tree.validate());
}

TEST(RBTreeTest, RemoveBlackNodeWithRedChild) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(20);
    tree.remove(15);

    EXPECT_FALSE(tree.contains(15));
    EXPECT_TRUE(tree.contains(20));
    EXPECT_TRUE(tree.validate());
}

TEST(RBTreeTest, MassRemoval) {
    RBTree<int> tree;
    for (int i = 1; i <= 100; ++i) {
        tree.insert(i);
    }

    for (int i = 1; i <= 100; ++i) {
        tree.remove(i);
        EXPECT_FALSE(tree.contains(i));
        EXPECT_TRUE(tree.validate());
    }

    EXPECT_TRUE(tree.isEmpty());
}

TEST(RBTreeTest, RemoveAndReinsert) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.remove(5);
    tree.insert(5);

    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(10));
    EXPECT_TRUE(tree.contains(15));
    EXPECT_TRUE(tree.validate());
}

TEST(RBTreeTest, RemoveNonExistentElement) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(5);

    tree.remove(15);

    EXPECT_TRUE(tree.contains(5));
    EXPECT_TRUE(tree.contains(10));
    EXPECT_FALSE(tree.contains(15));
    EXPECT_TRUE(tree.validate());
}

TEST(RBTreeTest, RemoveWithComplexRebalance) {
    RBTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(20);
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.insert(11);
    tree.insert(13);
    tree.insert(18);
    tree.insert(25);

    tree.remove(10);

    EXPECT_FALSE(tree.contains(10));
    EXPECT_TRUE(tree.validate());

    std::vector<int> remaining = { 5,15,3,7,12,20,1,4,6,8,11,13,18,25 };
    for (int val : remaining) {
        EXPECT_TRUE(tree.contains(val));
    }
}

TEST(RBTreeTest, RemoveAllElementsInReverseOrder) {
    RBTree<int> tree;
    for (int i = 1; i <= 100; ++i) {
        tree.insert(i);
    }

    for (int i = 100; i >= 1; --i) {
        tree.remove(i);
        EXPECT_FALSE(tree.contains(i));
        EXPECT_TRUE(tree.validate());
    }

    EXPECT_TRUE(tree.isEmpty());
}

TEST(RBTreeTest, RemoveWithAllCaseCoverage) {
    RBTree<int> tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(10);
    tree.insert(25);
    tree.insert(35);
    tree.insert(50);
    tree.insert(5);
    tree.insert(15);
    tree.insert(27);
    tree.insert(33);
    tree.insert(38);
    tree.insert(45);
    tree.insert(55);

    tree.remove(30);
    tree.remove(20);
    tree.remove(40);
    tree.remove(10);
    tree.remove(25);

    EXPECT_TRUE(tree.validate());

    std::vector<int> remaining = { 5,15,27,33,35,38,45,50,55 };
    for (int val : remaining) {
        EXPECT_TRUE(tree.contains(val));
    }
}
