// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include <string>
#include "../lib_unsort_table/untable.h"
#include "../lib_unsort_table/untable_mas.h"
#include "../lib_unsort_table/untable_tree.h"

TEST(UnsortedTableTest, FindMethod) {
    UnsortedTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
}

TEST(UnsortedTableTest, Insert_with_key) {
    UnsortedTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.find(3), "three");
    ASSERT_ANY_THROW(table.insert(1, "r"));
    EXPECT_EQ(table.find(1), "one");
}

TEST(UnsortedTableTest, OperatorBrackets) {
    UnsortedTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table[1], "one");
    EXPECT_EQ(table[3], "three");
}

TEST(UnsortedTableTest, Insert_without_key) {
    UnsortedTable<int, std::string> table;
    int key_one = table.insert("one");
    int key_two = table.insert("two");
    int key_three = table.insert("three");

    EXPECT_EQ(table.find(key_three), "three");
    EXPECT_EQ(table.find(key_one), "one");
    EXPECT_EQ(table.find(key_two), "two");
}

TEST(UnsortedTableTest, EraseMethod) {
    UnsortedTable<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");

    table.erase(2);

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(3), "three");

    EXPECT_THROW(table.erase(4), std::out_of_range);
    EXPECT_THROW(table.erase(2), std::out_of_range);
}

TEST(UnsortedTableOnMassTest, FindMethod) {
    UnsortedTableMas<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");
}

TEST(UnsortedTableOnMasTest, Insert_with_key) {
    UnsortedTableMas<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.find(3), "three");
    ASSERT_ANY_THROW(table.insert(1, "r"));
    EXPECT_EQ(table.find(1), "one");
}

TEST(UnsortedTableOnMasTest, OperatorBrackets) {
    UnsortedTableMas<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table[1], "one");
    EXPECT_EQ(table[3], "three");
}

TEST(UnsortedTableOnMasTest, Insert_without_key) {
    UnsortedTableMas<int, std::string> table;
    int key_one = table.insert("one");
    int key_two = table.insert("two");
    int key_three = table.insert("three");

    EXPECT_EQ(table.find(key_three), "three");
    EXPECT_EQ(table.find(key_one), "one");
    EXPECT_EQ(table.find(key_two), "two");
}

TEST(UnsortedTableOnMasTest, EraseMethod) {
    UnsortedTableMas<int, std::string> table;
    table.insert(1, "one");
    table.insert(2, "two");
    table.insert(3, "three");

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(2), "two");
    EXPECT_EQ(table.find(3), "three");

    table.erase(2);

    EXPECT_EQ(table.find(1), "one");
    EXPECT_EQ(table.find(3), "three");

    EXPECT_THROW(table.erase(4), std::out_of_range);
}

TEST(BinSearchTreeTableTest, FindMethod) {
    TBinSearchTree<TPair<int, int>> tree;
    for (int i = 0; i < 5; i++) {
        TPair<int, int> p(i, i * 10);
        tree.insert(p);
    }
    TBSTable<int, int> tab(tree);
    EXPECT_EQ(tab.find(2), 20);
    EXPECT_EQ(tab.find(4), 40);
}
