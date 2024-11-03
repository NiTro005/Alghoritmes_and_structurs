// Copyright 2024 Trofimov Nikita
#include <gtest.h>
#include "../lib_list/tlist.h"
#include "../lib_stackOnList/lstack.h"

TEST(Test_LStack, Constructor) {
    LStack<int> st1;
    EXPECT_EQ(st1.size(), 0);
    EXPECT_EQ(st1.capacity(), 20);
}

TEST(Test_LStack, empty_metod) {
    LStack<int> st1;
    EXPECT_TRUE(st1.IsEmpty());
}

TEST(Test_LStack, PUSH_metod) {
    LStack<int> st1(3);
    st1.push(8);
    st1.push(7);
    st1.push(1);
    EXPECT_EQ(st1.top(), 1);
    EXPECT_EQ(st1.size(), 3);
    ASSERT_ANY_THROW(st1.push(2));
}

TEST(Test_LStack, POP_metod) {
    LStack<int> st1(5);

    ASSERT_ANY_THROW(st1.pop());

    st1.push(1);
    st1.push(2);
    st1.push(3);
    st1.pop();
    EXPECT_EQ(st1.top(), 2);
    EXPECT_EQ(st1.size(), 2);
}

TEST(Test_LStack, Full_metod) {
    LStack<int> st1(2);
    st1.push(2);
    st1.push(3);
    EXPECT_TRUE(st1.IsFull());


    ASSERT_ANY_THROW(st1.push(2));
}
