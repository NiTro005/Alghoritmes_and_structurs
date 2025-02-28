// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include <string>
#include "../lib_sorted_table/stable_on_mas.h"

TEST(Test_SortedTableOnMAs, test_constructor_init) {
    TDMassive<TPair<int, int>> mas;
    for (int i = 0; i < 5; i++) {
        TPair<int, int> p(i, i);
        mas.push_back(p);
    }
    SortedTabOnMas<int, int> tab(mas);
    EXPECT_EQ(tab[0], 0);
    EXPECT_EQ(tab[1], 1);
    EXPECT_EQ(tab[2], 2);
}

TEST(Test_SortedTableOnMAs, test_constructor_init_with_not_sorted_array) {
    TDMassive<TPair<int, int>> mas;
    for (int i = 0; i < 5; i++) {
        TPair<int, int> p(5-i, i);
        mas.push_back(p);
    }
    SortedTabOnMas<int, int> tab(mas);
    EXPECT_EQ(tab[1], 4);
    EXPECT_EQ(tab[2], 3);
    EXPECT_EQ(tab[5], 0);
}

TEST(Test_SortedTableOnMAs, test_find) {
    TDMassive<TPair<int, int>> mas;
    for (int i = 0; i < 5; i++) {
        TPair<int, int> p(i, i);
        mas.push_back(p);
    }
    SortedTabOnMas<int, int> tab(mas);

    EXPECT_EQ(tab.find(2), 2);
    EXPECT_EQ(tab.find(4), 4);
    ASSERT_ANY_THROW(tab.find(5));
}

TEST(Test_SortedTableOnMAs, test_insert) {
    TDMassive<TPair<int, int>> mas;
    for (int i = 0; i < 5; i++) {
        TPair<int, int> p(i * 2, i);
        mas.push_back(p);
    }
    SortedTabOnMas<int, int> tab(mas);
    EXPECT_EQ(tab[0], 0);
    EXPECT_EQ(tab[2], 1);
    EXPECT_EQ(tab[4], 2);
    ASSERT_ANY_THROW(tab.find(1));
    tab.insert(1, 6);
    EXPECT_EQ(tab[0], 0);
    EXPECT_EQ(tab[1], 6);
    EXPECT_EQ(tab[2], 1);
}

TEST(Test_SortedTableOnMAs, test_erase) {
    SortedTabOnMas<int, int> tab;
    tab.insert(1, 3);
    tab.insert(5, 7);
    tab.insert(3, 2);
    EXPECT_EQ(tab[1], 3);
    EXPECT_EQ(tab[5], 7);
    EXPECT_EQ(tab[3], 2);
    tab.erase(5);
    ASSERT_ANY_THROW(tab.find(5));
    ASSERT_ANY_THROW(tab.erase(6));
}
