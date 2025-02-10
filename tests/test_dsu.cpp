// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include "../lib_dsu/dsu.h"

TEST(TestDSU, testMake_Set) {
    DSU dsu(7);
    dsu.make_set(1);
    dsu.make_set(4);
    EXPECT_EQ(dsu.parent(1), 1);
    EXPECT_EQ(dsu.parent(4), 4);
    ASSERT_ANY_THROW(dsu.make_set(-1));
    ASSERT_ANY_THROW(dsu.make_set(0));
}
