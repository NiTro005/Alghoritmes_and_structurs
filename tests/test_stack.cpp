// Copyright 2024 Trofimov Nikita
#include <gtest.h>
#include "../lib_dmassive/archive.h"
#include "../lib_stack/stack.h"

TEST(Test_TStack, Constructor) {
    TStack<int> st1;
    EXPECT_EQ(st1.size(), 20);
}

TEST(Test_TStack, empty_metod) {
    TStack<int> st1;
    EXPECT_TRUE(st1.IsEmpty());
}

TEST(Test_TStack, PUSH_metod) {
    TStack<int> st1(3);
    st1.push(8);
    st1.push(7);
    st1.push(1);
    EXPECT_EQ(st1.top(), 1);
}

TEST(Test_TStack, POP_metod) {
    TStack<int> st1(5);

    ASSERT_ANY_THROW(st1.pop());

    st1.push(1);
    st1.push(2);
    st1.push(3);
    st1.pop();
    EXPECT_EQ(st1.top(), 2);
}

TEST(Test_TStack, Full_metod) {
    TStack<int> st1(2);
    st1.push(2);
    st1.push(3);
    EXPECT_TRUE(st1.IsFull());


    ASSERT_ANY_THROW(st1.push(2));
}

TEST(Test_TStack, Top_metod) {
    TStack<int> st1(2);
    st1.push(2);
    st1.push(3);
    EXPECT_EQ(st1.top(), 3);
    st1.pop();
    EXPECT_EQ(st1.top(), 2);
    st1.pop();
    ASSERT_ANY_THROW(st1.top());
}
