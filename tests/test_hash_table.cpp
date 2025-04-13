// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include <string>
#include "../lib_string/cstring.h"
#include "../lib_hash_table/hash_table.h"

TEST(Hash_table_TEST, insert_method) {
    HashTable<int, int> tab(OpenAddress);
    tab.insert(1265, 3);
    EXPECT_EQ(tab.find(1265), 3);
}

TEST(Hash_table_TEST, insert_string_method) {
    HashTable<std::string, int> tab(OpenAddress);
    tab.insert("Hello", 3);
    EXPECT_EQ(tab.find("Hello"), 3);
}
