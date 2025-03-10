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

    EXPECT_EQ(tree.search(10)->get_value(), 10);
    EXPECT_EQ(tree.search(5)->get_value(), 5);
    EXPECT_EQ(tree.search(15)->get_value(), 15);
    EXPECT_EQ(tree.search(6)->get_value(), 6);
    EXPECT_EQ(tree.search(11)->get_value(), 11);
}

TEST(TBinSearchTreeTest, EraseLeafNode) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);

    tree.erase(3);
    EXPECT_EQ(tree.search(3)->get_value(), 5);
    EXPECT_EQ(tree.search(5)->get_value(), 5);
    EXPECT_EQ(tree.search(10)->get_value(), 10);
    EXPECT_EQ(tree.search(15)->get_value(), 15);
}

TEST(TBinSearchTreeTest, EraseNodeWithLeftChild) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(3);

    tree.erase(5);

    EXPECT_EQ(tree.search(5)->get_value(), 3);
    EXPECT_EQ(tree.search(3)->get_value(), 3);
    EXPECT_EQ(tree.search(10)->get_value(), 10);
}

TEST(TBinSearchTreeTest, EraseNodeWithRightChild) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(7);

    tree.erase(5);

    EXPECT_EQ(tree.search(5)->get_value(), 7);
    EXPECT_EQ(tree.search(7)->get_value(), 7);
    EXPECT_EQ(tree.search(10)->get_value(), 10);
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

    EXPECT_EQ(tree.search(15)->get_value(), 12);
    EXPECT_EQ(tree.search(12)->get_value(), 12);
    EXPECT_EQ(tree.search(17)->get_value(), 17);
    EXPECT_EQ(tree.search(10)->get_value(), 10);
    EXPECT_EQ(tree.search(5)->get_value(), 5);
    EXPECT_EQ(tree.search(3)->get_value(), 3);
    EXPECT_EQ(tree.search(7)->get_value(), 7);
}

TEST(TBinSearchTreeTest, EraseRootNode) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    tree.erase(10);

    EXPECT_EQ(tree.search(10)->get_value(), 5);
    EXPECT_EQ(tree.search(5)->get_value(), 5);
    EXPECT_EQ(tree.search(15)->get_value(), 15);
}

TEST(TBinSearchTreeTest, EraseFromMidle) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(17);
    tree.insert(20);

    tree.erase(15);
    EXPECT_EQ(tree.search(15)->get_value(), 17);
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

TEST(TBinSearchTreeTest, size_test) {
    TBinSearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(17);

    EXPECT_EQ(tree.size(), 7);
}
