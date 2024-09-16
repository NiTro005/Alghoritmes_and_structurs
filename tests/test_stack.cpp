// Copyright 2024 Trofimov Nikita
#include <gtest.h>
#include "../lib_dmassive/archive.h"
#include "../lib_stack/stack.h"

//TEST(Test_TStack, Constructor) {
//	TStack<int> st1;
//	EXPECT_EQ(st1.size(), 20);
//}

TEST(Test_TStack, empty_metod) {
	TStack<int> st1;
	EXPECT_TRUE(st1.IsEmpty());
}

TEST(Test_TStack, PUSH_metod) {
	TStack<int> st1(1);
	st1.push(1);
	ASSERT_ANY_THROW(st1.push(2));
	EXPECT_EQ(st1.top(), 1);
}