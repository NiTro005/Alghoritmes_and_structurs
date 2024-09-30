// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include "../lib_list/tnode.h"

TEST(TNodeTest, DefaultConstructor) {
    TNode<int> node(5);
    EXPECT_EQ(node.value(), 5);
    EXPECT_EQ(node.next(), nullptr);
}

TEST(TNodeTest, CopyConstructor) {
    TNode<int> node1(5);
    TNode<int> node2(node1);
    EXPECT_EQ(node2.value(), 5);
    EXPECT_EQ(node2.next(), nullptr);
}

TEST(TNodeTest, NextMethod) {
    TNode<int> node1(5);
    TNode<int> node2(10, &node1);
    EXPECT_EQ(node2.next(), &node1);
}

TEST(TNodeTest, SetNextMethod) {
    TNode<int> node1(5);
    TNode<int> node2(10);
    node2.next(&node1);
    EXPECT_EQ(node2.next(), &node1);
}

TEST(TNodeTest, ValueMethod) {
    TNode<int> node(5);
    EXPECT_EQ(node.value(), 5);
}

TEST(TNodeTest, AssignmentOperator) {
    TNode<int> node1(5);
    TNode<int> node2(10);
    node2 = node1;
    EXPECT_EQ(node2.value(), 5);
    EXPECT_EQ(node2.next(), nullptr);
}

TEST(TNodeTest, EqualityOperator) {
    TNode<int> node1(5);
    TNode<int> node2(5);
    EXPECT_TRUE(node1 == 5);
    EXPECT_TRUE(node2 == 5);
}