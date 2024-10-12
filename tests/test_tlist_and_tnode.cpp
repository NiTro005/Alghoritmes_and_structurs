// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include "../lib_list/tnode.h"
#include "../lib_list/tlist.h"

template <typename T>
TList<T>* createList(int size) {
    TList<T>* list = new TList<T>();
    for (int i = 0; i < size; ++i) {
        list->push_back(i);
    }
    return list;
}

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

TEST(TListTest, PushFront) {
    TList<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    EXPECT_EQ(list.head->value(), 3);
    EXPECT_EQ(list.head->next()->value(), 2);
    EXPECT_EQ(list.head->next()->next()->value(), 1);
    EXPECT_EQ(list.head->next()->next()->next(), nullptr);
    EXPECT_EQ(list.last->value(), 1);
}

TEST(TListTest, PushBack) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.head->value(), 1);
    EXPECT_EQ(list.head->next()->value(), 2);
    EXPECT_EQ(list.head->next()->next()->next(), nullptr);
    EXPECT_EQ(list.last->value(), 3);
}

TEST(TListTest, InsertNode) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.insert(list.head->next(), 4);

    EXPECT_EQ(list.head->value(), 1);
    EXPECT_EQ(list.head->next()->value(), 2);
    EXPECT_EQ(list.head->next()->next()->value(), 4);
    EXPECT_EQ(list.head->next()->next()->next()->value(), 3);
    EXPECT_EQ(list.head->next()->next()->next()->next(), nullptr);
    EXPECT_EQ(list.last->value(), 3);
}

TEST(TListTest, InsertPosition) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.insert(1, 4);

    EXPECT_EQ(list.head->value(), 1);
    EXPECT_EQ(list.head->next()->value(), 2);
    EXPECT_EQ(list.head->next()->next()->value(), 4);
    EXPECT_EQ(list.head->next()->next()->next()->value(), 3);
    EXPECT_EQ(list.head->next()->next()->next()->next(), nullptr);
    EXPECT_EQ(list.last->value(), 3);
}

TEST(TListTest, InsertPositionOutOfRange) {
    TList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_THROW(list.insert(4, 4), std::logic_error);
}

TEST(TListTest, TListDestructor) {
    TList<int>* list = createList<int>(10);
    delete list;
}

TEST(TListTest, TListFind_method) {
    TList<int>* list = createList<int>(10);
    TNode<int>* find;
    find = list->find(2);
    EXPECT_EQ(find->value(), 2);
    EXPECT_EQ(find->next(), list->head->next()->next()->next());
}

TEST(TListTest, TListPopBack_method) {
    TList<int>* list = createList<int>(4);
    EXPECT_EQ(list->last->value(), 3);
    list->pop_back();
    EXPECT_EQ(list->last->value(), 2);
    list->pop_front();
    list->pop_front();
    list->pop_front();
    ASSERT_ANY_THROW(list->pop_back());
}

TEST(TListTest, TListPopFront_method) {
    TList<int>* list = createList<int>(4);
    EXPECT_EQ(list->head->value(), 0);
    list->pop_front();
    EXPECT_EQ(list->head->value(), 1);
    list->pop_front();
    list->pop_front();
    list->pop_front();
    ASSERT_ANY_THROW(list->pop_front());
}

TEST(TListTest, TListEraseLink_method) {
    TList<int>* list = createList<int>(4);
    EXPECT_EQ(list->head->next()->value(), 1);
    EXPECT_EQ(list->head->next()->next()->value(), 2);
    list->erase(list->head->next());
    EXPECT_EQ(list->head->next()->value(), 1);
    EXPECT_EQ(list->head->next()->next()->value(), 3);
    ASSERT_ANY_THROW(list->erase(nullptr));
}


TEST(TListTest, TListErasePos_method) {
    TList<int>* list = createList<int>(4);
    EXPECT_EQ(list->head->next()->value(), 1);
    EXPECT_EQ(list->head->next()->next()->value(), 2);
    list->erase(1);
    EXPECT_EQ(list->head->next()->value(), 1);
    EXPECT_EQ(list->head->next()->next()->value(), 3);
    ASSERT_ANY_THROW(list->erase(7));
}

TEST(TListTest, TListReplaceLink_method) {
    TList<int>* list = createList<int>(4);
    EXPECT_EQ(list->head->next()->value(), 1);
    EXPECT_EQ(list->head->next()->next()->value(), 2);
    list->replace(list->head->next(), 4);
    EXPECT_EQ(list->head->next()->value(), 4);
    EXPECT_EQ(list->head->next()->next()->value(), 2);

    ASSERT_ANY_THROW(list->replace(nullptr, 5));
}


TEST(TListTest, TListReplacePos_method) {
    TList<int>* list = createList<int>(4);
    EXPECT_EQ(list->head->next()->value(), 1);
    EXPECT_EQ(list->head->next()->next()->value(), 2);
    list->replace(1, 5);
    EXPECT_EQ(list->head->next()->value(), 5);
    EXPECT_EQ(list->head->next()->next()->value(), 2);

    ASSERT_ANY_THROW(list->replace(7, 5));
}

TEST(TListTest, TListAssort) {
    TList<int>* list = new TList<int>();
    list->push_back(5);
    list->push_back(1);
    list->push_back(8);
    list->push_back(9);
    list->push_back(2);

    asort(*list);

    EXPECT_EQ(list->head->value(), 1);
    EXPECT_EQ(list->head->next()->value(), 2);
    EXPECT_EQ(list->head->next()->next()->value(), 5);
    EXPECT_EQ(list->head->next()->next()->next()->value(), 8);
    EXPECT_EQ(list->head->next()->next()->next()->next()->value(), 9);
    EXPECT_EQ(list->last->value(), 9);
}