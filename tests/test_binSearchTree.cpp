// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include "../lib_binSearchTree/binSearchTree.h"

TEST(TBinSearchTreeTest, InsertAndSearch) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(6);
    tree.insert(11);

    EXPECT_EQ(tree.search(10)->value, 10);
    EXPECT_EQ(tree.search(5)->value, 5);
    EXPECT_EQ(tree.search(15)->value, 15);
    EXPECT_EQ(tree.search(6)->value, 6);
    EXPECT_EQ(tree.search(11)->value, 11);
}

TEST(TBinSearchTreeTest, EraseLeafNode) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);

    tree.erase(3);
    EXPECT_EQ(tree.search(3)->value, 5);
    EXPECT_EQ(tree.search(5)->value, 5);
    EXPECT_EQ(tree.search(10)->value, 10);
    EXPECT_EQ(tree.search(15)->value, 15);
}

TEST(TBinSearchTreeTest, EraseNodeWithLeftChild) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(3);

    tree.erase(5);

    EXPECT_EQ(tree.search(5)->value, 3);
    EXPECT_EQ(tree.search(3)->value, 3);
    EXPECT_EQ(tree.search(10)->value, 10);
}

TEST(TBinSearchTreeTest, EraseNodeWithRightChild) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(7);

    tree.erase(5);

    EXPECT_EQ(tree.search(5)->value, 7);
    EXPECT_EQ(tree.search(7)->value, 7);
    EXPECT_EQ(tree.search(10)->value, 10);
}

TEST(TBinSearchTreeTest, EraseNodeWithTwoChildren) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(17);

    tree.erase(15);

    EXPECT_EQ(tree.search(15)->value, 12);
    EXPECT_EQ(tree.search(12)->value, 12);
    EXPECT_EQ(tree.search(17)->value, 17);
    EXPECT_EQ(tree.search(10)->value, 10);
    EXPECT_EQ(tree.search(5)->value, 5);
    EXPECT_EQ(tree.search(3)->value, 3);
    EXPECT_EQ(tree.search(7)->value, 7);
}

TEST(TBinSearchTreeTest, EraseRootNode) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.erase(10);

    EXPECT_EQ(tree.search(10)->value, 5);
    EXPECT_EQ(tree.search(5)->value, 5);
    EXPECT_EQ(tree.search(15)->value, 15);
}

TEST(TBinSearchTreeTest, EraseNonExistentValue) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    EXPECT_THROW(tree.erase(100), std::logic_error);
}

TEST(TBinSearchTreeTest, Clear) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.clear();
    EXPECT_EQ(tree.search(10), nullptr);
    EXPECT_EQ(tree.search(5), nullptr);
    EXPECT_EQ(tree.search(15), nullptr);
}

TEST(TBinSearchTreeTest, InsertDuplicate) {
    TBinSearchTree<int> tree;
    tree.insert(10);

    EXPECT_THROW(tree.insert(10), std::logic_error);
}

TEST(TBinSearchTreeTest, EraseNonExistent) {
    TBinSearchTree<int> tree;
    tree.insert(10);

    EXPECT_THROW(tree.erase(20), std::logic_error);
}
