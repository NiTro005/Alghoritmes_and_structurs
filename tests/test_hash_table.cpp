// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include <string>
#include "../lib_string/cstring.h"
#include "../lib_hash_table/hash_table.h"

TEST(HashTableTest, InsertIntKey) {
    HashTable<int, int> tab(OpenAddress);
    tab.insert(1265, 3);
    EXPECT_EQ(tab.find(1265), 3);
}

TEST(HashTableTest, InsertStringKey) {
    HashTable<std::string, int> tab(OpenAddress);
    tab.insert("Hello", 3);
    EXPECT_EQ(tab.find("Hello"), 3);
}

TEST(HashTableTest, UpdateValue) {
    HashTable<int, std::string> tab(OpenAddress);
    tab.insert(1, "one");
    tab.insert(1, "new one");
    EXPECT_EQ(tab.find(1), "new one");
}

TEST(HashTableTest, RemoveElement) {
    HashTable<int, int> tab(OpenAddress);
    tab.insert(10, 100);
    tab.erase(10);
    EXPECT_THROW(tab.find(10), std::logic_error);
}

TEST(HashTableTest, OperatorBrackets) {
    HashTable<int, std::string> tab(OpenAddress);
    tab.insert(5, "five");
    EXPECT_EQ(tab[5], "five");
}

TEST(HashTableTest, FindNonExistentKey) {
    HashTable<int, int> tab(OpenAddress);
    EXPECT_THROW(tab.find(999), std::logic_error);
}

TEST(HashTableTest, RemoveNonExistentKey) {
    HashTable<int, int> tab(OpenAddress);
    EXPECT_THROW(tab.erase(999), std::logic_error);
}

TEST(HashTableTest, EmptyTableOperations) {
    HashTable<int, int> tab(OpenAddress);
    EXPECT_THROW(tab.find(1), std::logic_error);
    EXPECT_THROW(tab.erase(1), std::logic_error);
}

TEST(HashTableTest, HandleStringCollisions) {
    HashTable<std::string, std::string> tab(OpenAddress);

    tab.insert("pol", "value1");
    tab.insert("ned", "value2");

    EXPECT_EQ(tab.find("pol"), "value1");
    EXPECT_EQ(tab.find("ned"), "value2");


    EXPECT_EQ(tab.find("pol"), "value1");
    EXPECT_EQ(tab.find("ned"), "value2");

    tab.insert("new_key_same_hash", "value3");
    EXPECT_EQ(tab.find("new_key_same_hash"), "value3");
    EXPECT_EQ(tab.find("ned"), "value2");
}

TEST(HashTableTest, DifferentDataTypes) {
    HashTable<std::string, double> tab(OpenAddress);
    tab.insert("pi", 3.14159);
    tab.insert("e", 2.71828);

    EXPECT_DOUBLE_EQ(tab.find("pi"), 3.14159);
    EXPECT_DOUBLE_EQ(tab.find("e"), 2.71828);
}
