// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include "../lib_vector/tvector.h"

TEST(TVectorTest, DefaultConstructor) {
    TVector<int> vec;
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0);
}

TEST(TVectorTest, FillConstructor) {
    TVector<int> vec(3, 5);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 5);
    EXPECT_EQ(vec[2], 5);
}

TEST(TVectorTest, CopyConstructor) {
    TVector<int> vec1(3, 5);
    TVector<int> vec2(vec1);
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec2[0], 5);
    EXPECT_EQ(vec2[1], 5);
    EXPECT_EQ(vec2[2], 5);
}

TEST(TVectorTest, Size_method) {
    TVector<int> vec(11, 6);
    vec.push_front(1);
    EXPECT_EQ(vec.size(), 1);
}