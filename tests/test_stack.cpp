// Copyright 2024 Trofimov Nikita
#include <gtest.h>
#include "../lib_dmassive/archive.h"
#include "../lib_stack/stack.h"

TEST(Test_TStack, Constructor) {
	TStack<int> st1;
	EXPECT_EQ(st1.size(), 20);
}