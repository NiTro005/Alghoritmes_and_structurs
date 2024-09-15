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

TEST(Test_TDMassive, get_size_function) {
    TDMassive<int> m;
    EXPECT_EQ(m.size(), 0);
    m.push_front(1);
    EXPECT_EQ(m.size(), 1);
    m.push_front(2);
    EXPECT_EQ(m.size(), 2);
}

TEST(Test_TDMassive, get_capacity_function) {
    TDMassive<int> m;
    EXPECT_EQ(m.capacity(), 15);
    m.resize(16, 1);
    EXPECT_GT(m.capacity(), 15);
}

TEST(Test_TDMassive, get_data_function) {
    TDMassive<int> m;
    m.push_front(1);
    m.push_front(2);
    const int* data = m.data();
    EXPECT_EQ(data[0], 2);
    EXPECT_EQ(data[1], 1);
}

TEST(Test_TDMassive, swap_function) {
    TDMassive<int> m(17, 5);
    TDMassive<int> d(2, 7);
    m.swap(d);
    EXPECT_EQ(m.size(), 2);
    EXPECT_EQ(d.size(), 17);
    EXPECT_EQ(d.data()[16], 5);
    EXPECT_EQ(m.data()[1], 7);
    EXPECT_NE(m.data()[4], 5);
    EXPECT_EQ(m.capacity(), 15);
    EXPECT_EQ(d.capacity(), 30);
}

TEST(Test_TDMassive, assign_function) {
    TDMassive<int> m(17, 5);
    TDMassive<int> d(2, 7);
    m.assign(d);
    EXPECT_EQ(m.size(), 2);
    EXPECT_EQ(m.data()[1], 7);
    EXPECT_EQ(m.capacity(), 15);
}
