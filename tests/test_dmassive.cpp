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

TEST(Test_TDMassive, clear_function) {
    TDMassive<int> m(17, 5);
    m.resize(12);
    m.clear();
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.capacity(), 0);
}

TEST(Test_TDMassive, repacking_function) {
    TDMassive<int> m;
    m.push_front(1);
    m.push_front(2);
    m.push_front(3);
    m.push_front(4);
    m.push_front(5);

    EXPECT_EQ(m.size(), 5);
    m.remove_by_index(1);
    m.remove_by_index(3);
    EXPECT_EQ(m.size(), 5);

    m.reserve();
    EXPECT_EQ(m.size(), 3);
    EXPECT_EQ(m.size(), 3);
    EXPECT_EQ(m.data()[0], 5);
    EXPECT_EQ(m.data()[1], 3);
    EXPECT_EQ(m.data()[2], 1);
}

TEST(Test_TDMassive, reserve_function) {
    TDMassive<int> m;
    m.resize(15, 5);
    EXPECT_EQ(m.capacity(), 15);
    m.push_front(1);
    m.reserve();
    EXPECT_EQ(m.capacity(), 30);
}

TEST(Test_TDMassive, resize_function) {
    TDMassive<int> m;
    m.resize(15, 5);
    EXPECT_EQ(m.size(), 15);
    m.resize(10);
    EXPECT_EQ(m.size(), 10);
}

TEST(Test_TDMassive, insert_single_value) {
    TDMassive<int> m;
    m.insert(1, 0);
    EXPECT_EQ(m.size(), 1);
    EXPECT_EQ(m.data()[0], 1);

    m.insert(2, 1);
    EXPECT_EQ(m.size(), 2);
    EXPECT_EQ(m.data()[0], 1);
    EXPECT_EQ(m.data()[1], 2);

    ASSERT_NO_THROW(m.insert(0, 0));
}

TEST(Test_TDMassive, insert_any_throw_single_value) {
    TDMassive<int> m;
    m.insert(1, 0);
    ASSERT_ANY_THROW(m.insert(0, 2));
}

TEST(Test_TDMassive, insert_array) {
    TDMassive<int> m;
    int arr[] = { 1, 2, 3 };
    m.insert(arr, 3, 0);
    EXPECT_EQ(m.size(), 3);
    EXPECT_EQ(m.data()[0], 1);
    EXPECT_EQ(m.data()[1], 2);
    EXPECT_EQ(m.data()[2], 3);
}

TEST(Test_TDMassive, insert_array_any_throw) {
    TDMassive<int> m;
    int arr[] = { 1, 2, 3 };
    ASSERT_ANY_THROW(m.insert(arr, 3, 1));
}

TEST(Test_TDMassive, PushBack) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(3);

    EXPECT_EQ(mass.data()[0], 1);
    EXPECT_EQ(mass.data()[1], 2);
    EXPECT_EQ(mass.data()[2], 3);
    EXPECT_EQ(mass.size(), 3);
}

TEST(Test_TDMassive, PushFront) {
    TDMassive<int> mass(10);
    mass.push_front(1);
    mass.push_front(2);
    mass.push_front(3);

    EXPECT_EQ(mass.data()[0], 3);
    EXPECT_EQ(mass.data()[1], 2);
    EXPECT_EQ(mass.data()[2], 1);
    EXPECT_EQ(mass.size(), 3);
}

TEST(Test_TDMassive, PopFront) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(3);

    mass.pop_front();
    EXPECT_EQ(mass[0], 2);
    EXPECT_EQ(mass[1], 3);
    EXPECT_EQ(mass.size(), 3);

    mass.pop_front();
    EXPECT_EQ(mass[0], 3);
    EXPECT_EQ(mass.size(), 3);

    mass.pop_front();
    EXPECT_EQ(mass.size(), 3);
}

TEST(Test_TDMassive, PopFront_any_throw) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    ASSERT_NO_THROW(mass.pop_front());
    ASSERT_ANY_THROW(mass.pop_front());
}
TEST(Test_TDMassive, PopBack) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(3);

    mass.pop_back();
    EXPECT_EQ(mass.data()[0], 1);
    EXPECT_EQ(mass.data()[1], 2);
    EXPECT_EQ(mass.size(), 2);

    mass.pop_back();
    EXPECT_EQ(mass.data()[0], 1);
    EXPECT_EQ(mass.size(), 1);

    mass.pop_back();
    EXPECT_EQ(mass.size(), 0);
}

TEST(Test_TDMassive, PopBack_any_throw) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    ASSERT_NO_THROW(mass.pop_back());
    ASSERT_ANY_THROW(mass.pop_back());
}

TEST(Test_TDMassive, RemoveByIndex) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(3);

    mass.remove_by_index(1);
    EXPECT_EQ(mass.get_state(1), State::deleted);
}

TEST(Test_TDMassive, RemoveByIndex_any_throw) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    ASSERT_NO_THROW(mass.remove_by_index(0));
    mass.push_back(1);
    ASSERT_ANY_THROW(mass.remove_by_index(3));
    ASSERT_NO_THROW(mass.remove_by_index(0));
    ASSERT_ANY_THROW(mass.remove_by_index(0));
}


TEST(Test_TDMassive, Erase) {
    TDMassive<int> mass(3);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(3);

    mass.erase(1, 4);
    EXPECT_EQ(mass.get_state(1), State::deleted);
    EXPECT_EQ(mass.get_state(2), State::deleted);
}

TEST(Test_TDMassive, Erase_any_throw) {
    TDMassive<int> mass(3);
    ASSERT_ANY_THROW(mass.erase(0, 5));
}

TEST(Test_TDMassive, RemoveAll) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(1);
    mass.push_back(3);

    mass.remove_all(1);
    EXPECT_EQ(mass.get_state(0), State::deleted);
    EXPECT_EQ(mass.get_state(2), State::deleted);
}

TEST(Test_TDMassive, RemoveAll_any_throw) {
    TDMassive<int> mass(3);
    ASSERT_ANY_THROW(mass.remove_all(0));
}

TEST(Test_TDMassive, RemoveFirst) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(1);
    mass.push_back(3);

    mass.remove_first(1);
    EXPECT_EQ(mass.get_state(0), State::deleted);
}

TEST(Test_TDMassive, RemoveFirst_any_throw) {
    TDMassive<int> mass(3);
    ASSERT_ANY_THROW(mass.remove_first(0));
}

TEST(Test_TDMassive, RemoveLast) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(1);
    mass.push_back(3);

    mass.remove_last(1);
    EXPECT_EQ(mass.get_state(2), State::deleted);
}

TEST(Test_TDMassive, RemoveLast_any_throw) {
    TDMassive<int> mass(3);
    ASSERT_ANY_THROW(mass.remove_last(0));
}

TEST(Test_TDMassive, FindFirst) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(1);
    mass.push_back(3);

    EXPECT_EQ(mass.find_first(1), 0);
    EXPECT_EQ(mass.find_first(2), 1);
    EXPECT_EQ(mass.find_first(3), 3);
}


TEST(Test_TDMassive, FindLast) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(1);
    mass.push_back(3);

    EXPECT_EQ(mass.find_last(1), 2);
    EXPECT_EQ(mass.find_last(2), 1);
    EXPECT_EQ(mass.find_last(3), 3);
}


TEST(Test_TDMassive, FindAll) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(1);
    mass.push_back(3);

    size_t* result = mass.find_all(1);
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[2], 2);
    delete[] result;

    result = mass.find_all(2);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 1);
    delete[] result;

    result = mass.find_all(3);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 3);
    delete[] result;
}

TEST(Test_TDMassive, Replace) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(3);

    mass.replace(1, 10);
    EXPECT_EQ(mass.data()[1], 10);
    EXPECT_EQ(mass.get_state(1), State::busy);

    mass.replace(0, 20);
    EXPECT_EQ(mass.data()[0], 20);
    EXPECT_EQ(mass.get_state(0), State::busy);
    ASSERT_ANY_THROW(mass.replace(12, 2));
}

TEST(Test_TDMassive, OperatorBrackets) {
    TDMassive<int> mass(10);
    mass.push_back(1);
    mass.push_back(2);
    mass.push_back(3);

    EXPECT_EQ(mass[0], 1);
    EXPECT_EQ(mass[1], 2);
    EXPECT_EQ(mass[2], 3);

    mass[0] = 10;
    mass[1] = 20;
    mass[2] = 30;

    EXPECT_EQ(mass[0], 10);
    EXPECT_EQ(mass[1], 20);
    EXPECT_EQ(mass[2], 30);
}
