// Copyright 2024 Trofimov Nikita
#include <gtest.h>
#include "../lib_pair/pair.h"

TEST(TPairTest, SetMethods) {
    TPair<int, int> pair1(1, 2);
    pair1.set_first(3);
    pair1.set_second(4);
    EXPECT_EQ(pair1.first(), 3);
    EXPECT_EQ(pair1.second(), 4);
}

TEST(TPairTest, AssignmentOperator) {
    TPair<int, int> pair1(1, 2);
    TPair<int, int> pair2 = pair1;
    EXPECT_EQ(pair2.first(), 1);
    EXPECT_EQ(pair2.second(), 2);
}

