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

TEST(HashTableChainTest, BasicInsertAndFind) {
    HashTable<int, std::string> tab(Chain);
    tab.insert(1, "one");
    tab.insert(2, "two");
    EXPECT_EQ(tab.find(1), "one");
    EXPECT_EQ(tab.find(2), "two");
}

TEST(HashTableChainTest, UpdateValue) {
    HashTable<std::string, int> tab(Chain);
    tab.insert("apple", 10);
    tab.insert("apple", 20);
    EXPECT_EQ(tab.find("apple"), 20);
}

TEST(HashTableChainTest, RemoveElement) {
    HashTable<int, double> tab(Chain);
    tab.insert(10, 3.14);
    tab.erase(10);
    EXPECT_THROW(tab.find(10), std::logic_error);
}

TEST(HashTableChainTest, HandleCollisions) {
    HashTable<int, std::string> tab(Chain);
    tab.insert(1, "first");
    tab.insert(1 + CAPACITY, "second");
    EXPECT_EQ(tab.find(1), "first");
    EXPECT_EQ(tab.find(1 + CAPACITY), "second");
    tab.erase(1);
    EXPECT_THROW(tab.find(1), std::logic_error);
    EXPECT_EQ(tab.find(1 + CAPACITY), "second");
}

TEST(HashTableChainTest, LongChain) {
    HashTable<int, int> tab(Chain);
    const int n = 100;
    for (int i = 0; i < n; i++) {
        tab.insert(i * CAPACITY, i);
    }
    for (int i = 0; i < n; i++) {
        EXPECT_EQ(tab.find(i * CAPACITY), i);
    }
    for (int i = 0; i < n; i += 2) {
        tab.erase(i * CAPACITY);
    }
    for (int i = 1; i < n; i += 2) {
        EXPECT_EQ(tab.find(i * CAPACITY), i);
    }
}

TEST(HashTableChainTest, MixedOperations) {
    HashTable<std::string, std::string> tab(Chain);
    tab.insert("key1", "value1");
    tab.insert("key2", "value2");
    tab.insert("key3", "value3");
    tab.insert("key2", "new_value2");
    EXPECT_EQ(tab.find("key1"), "value1");
    EXPECT_EQ(tab.find("key2"), "new_value2");
    EXPECT_EQ(tab.find("key3"), "value3");
    tab.erase("key1");
    EXPECT_THROW(tab.find("key1"), std::logic_error);
    tab.insert("key4", "value4");
    EXPECT_EQ(tab.find("key4"), "value4");
}

TEST(HashTableChainTest, StressTest) {
    HashTable<int, int> tab(Chain);
    const int n = 10000;
    for (int i = 0; i < n; i++) {
        tab.insert(i, i * 2);
    }
    for (int i = 0; i < n; i++) {
        EXPECT_EQ(tab.find(i), i * 2);
    }
    for (int i = 0; i < n; i += 2) {
        tab.erase(i);
    }
    for (int i = 1; i < n; i += 2) {
        EXPECT_EQ(tab.find(i), i * 2);
    }
}
