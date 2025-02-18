// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include "../lib_unsort_table/untable.h"

TList<TPair<int, int>> setList(int size) {
    TList<TPair<int, int>> list;
    for (int i = 0; i < size; i++) {
        TPair<int, int> pair(i, i * 10);
        list.push_back(pair);
    }
    return list;
}

TEST(UnsortedTable, test_find_on_coorect_value) {
    TList<TPair<int, int>> pair = setList(10);
    UnsortedTable<int, int> un(pair);
    EXPECT_EQ(un.find(2), 20);
}