// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include "../lib_vector/tvector.h"

TEST(TVectorTest, DefaultConstructor) {
    TVector<int> vec;
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0);
}

TEST(TVectorTest, FillConstructor) {
    TVector<int> vec(8, 4);
    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0);
}

TEST(TVectorTest, Size_method) {
    TVector<int> vec(11, 6);
    vec.insert(1, 0);
    EXPECT_EQ(vec.size(), 1);
}

TEST(TVectorTest, Empty) {
    TVector<int> vec;
    EXPECT_TRUE(vec.empty());

    vec.push_back(1);
    EXPECT_FALSE(vec.empty());
}

TEST(TVectorTest, Size) {
    TVector<int> vec;
    EXPECT_EQ(vec.size(), 0);

    vec.push_back(1);
    EXPECT_EQ(vec.size(), 1);

    vec.push_back(2);
    EXPECT_EQ(vec.size(), 2);
}

TEST(TVectorTest, StartIndex) {
    TVector<int> vec;
    EXPECT_EQ(vec.start_index(), 0);

    vec.push_back(1);
    EXPECT_EQ(vec.start_index(), 0);
}

TEST(TVectorTest, Data) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    const int* data = vec.data();
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
    EXPECT_EQ(data[2], 3);
}

TEST(TVectorTest, Swap) {
    TVector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);

    TVector<int> vec2;
    vec2.push_back(3);
    vec2.push_back(4);

    vec1.swap(vec2);

    EXPECT_EQ(vec1.size(), 2);
    EXPECT_EQ(vec1[0], 3);
    EXPECT_EQ(vec1[1], 4);

    EXPECT_EQ(vec2.size(), 2);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
}

TEST(TVectorTest, Assign) {
    TVector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);

    TVector<int> vec2;
    vec2.assign(vec1);

    EXPECT_EQ(vec2.size(), 2);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
}

TEST(TVectorTest, Clear) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    vec.clear();

    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.size(), 0);
}

TEST(TVectorTest, Resize) {
    TVector<int> vec;
    vec.resize(5, 0);

    EXPECT_EQ(vec.size(), 5);
    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], 0);
    }
}

TEST(TVectorTest, PushBack) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

TEST(TVectorTest, PopBack) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    vec.pop_back();

    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 1);
}

TEST(TVectorTest, InsertArray) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    int arr[] = { 3, 4, 5 };
    vec.insert(arr, 3, 1);

    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec[2], 4);
    EXPECT_EQ(vec[3], 5);
    EXPECT_EQ(vec[4], 2);
}

TEST(TVectorTest, InsertValue) {
    TVector<int> vec(4, 1);
    vec.push_back(1);
    vec.push_back(2);

    vec.insert(3, 1);

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec[2], 2);
}

TEST(TVectorTest, Replace) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    vec.replace(1, 3);

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
}

TEST(TVectorTest, Erase) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    vec.erase(1, 1);
    vec.insert(4, 1);

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 4);
    EXPECT_EQ(vec[2], 3);
}

TEST(TVectorTest, FindAll) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(1);

    size_t* indices = vec.find_all(1);
    EXPECT_EQ(indices[0], 2);
    EXPECT_EQ(indices[1], 0);
    EXPECT_EQ(indices[2], 2);
}

TEST(TVectorTest, FindFirst) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(1);

    EXPECT_EQ(vec.find_first(1), 0);
}

TEST(TVectorTest, FindLast) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(1);

    EXPECT_EQ(vec.find_last(1), 2);
}

TEST(TVectorTest, OperatorAccess) {
    TVector<int> vec;
    vec.push_back(1);
    vec.push_back(2);

    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);

    vec[0] = 3;
    EXPECT_EQ(vec[0], 3);
}

TEST(TVectorTest, OperatorAssignment) {
    TVector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);

    TVector<int> vec2;
    vec2 = vec1;

    EXPECT_EQ(vec2.size(), 2);
    EXPECT_EQ(vec2[0], 1);
    EXPECT_EQ(vec2[1], 2);
}

TEST(TVectorTest, OperatorAddition) {
    TVector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);

    TVector<int> vec2;
    vec2.push_back(3);
    vec2.push_back(4);

    TVector<int> vec3 = vec1 + vec2;

    EXPECT_EQ(vec3.size(), 2);
    EXPECT_EQ(vec3[0], 4);
    EXPECT_EQ(vec3[1], 6);
}

TEST(TVectorTest, OperatorAdditionDifferentSizes) {
    TVector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    TVector<int> vec2;
    vec2.push_back(4);
    vec2.push_back(5);

    TVector<int> vec3 = vec1 + vec2;

    EXPECT_EQ(vec3.size(), 3);
    EXPECT_EQ(vec3[0], 5);
    EXPECT_EQ(vec3[1], 7);
    EXPECT_EQ(vec3[2], 3);
}

TEST(TVectorTest, OperatorAdditionDiffrentStart_index) {
    TVector<int> vec1(7, 1);
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    TVector<int> vec2;
    vec2.push_back(4);
    vec2.push_back(5);

    TVector<int> vec3 = vec1 + vec2;

    EXPECT_EQ(vec3.size(), 4);
    EXPECT_EQ(vec3[0], 4);
    EXPECT_EQ(vec3[1], 6);
    EXPECT_EQ(vec3[2], 7);
    EXPECT_EQ(vec3[3], 3);
}
