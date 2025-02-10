// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include "../lib_dsu/dsu.h"

TEST(DSUTest, UnionTest) {
    DSU dsu(5);
    dsu.Union(1, 2);
    EXPECT_EQ(dsu.parent(1), dsu.parent(2));

    dsu.Union(2, 3);
    EXPECT_EQ(dsu.parent(1), dsu.parent(3));

    dsu.Union(4, 5);
    EXPECT_EQ(dsu.parent(4), dsu.parent(5));

    dsu.Union(1, 4);
    EXPECT_EQ(dsu.find(1), dsu.find(4));
    EXPECT_EQ(dsu.find(2), dsu.find(5));

    ASSERT_ANY_THROW(dsu.Union(-1, 2));
}


TEST(TestDSU, testFind) {
    DSU dsu(7);
    EXPECT_EQ(dsu.find(3), 2);
    
    dsu.Union(2, 1);
    dsu.Union(3, 2);
    EXPECT_EQ(dsu.find(1), 1);
    EXPECT_EQ(dsu.find(3), 1);

    ASSERT_ANY_THROW(dsu.find(-1));
}
