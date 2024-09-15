// Copyright 2024 Trofimov Nikita
#include <gtest.h>
#include "../lib_dmassive/archive.h"

TEST(Test_TDMassive, empty_function) {
	TDMassive<int> m;
	EXPECT_TRUE(m.empty());
	m.push_front(1);
	EXPECT_FALSE(m.empty());
}

TEST(Test_TDMassive, full_function) {
	TDMassive<int> m;
	EXPECT_FALSE(m.full());
	m.resize(15, 'a');
	EXPECT_TRUE(m.full());
}