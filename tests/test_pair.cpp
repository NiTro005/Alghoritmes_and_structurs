
#include <gtest.h>

#include "../lib_pair/pair.h"


TEST(TestPairLib, WorkOnAllTipe) {
	TPair <int, int> tipe1(1, 2);
	TPair <int, float> tipe2(1, 2.2);
	TPair <int, char> tipe3(1, 'a');
	TPair <int, bool> tipe4(1, true);
	TPair <float, char> tipe5(1, 'a');
	TPair <float, bool> tipe6(1, false);
	TPair <char, bool> tipe7('a', true);
	TPair <bool, bool> tipe8(true, false);
	ASSERT_NO_THROW(tipe1, tipe2, tipe3, tipe4, tipe5, tipe6, tipe7, tipe8);
}

TEST(TestPairLib, CheckOperatorPlusRavno) {
	TPair<int, int> t(1, 4);
	TPair<int, int> t1(10, 10);

	t1 += t;

	EXPECT_EQ(t1.first(), 11);
	EXPECT_EQ(t1.second(), 14);
}

TEST(TestPairLib, CheckOperatorMinusRavno) {
	TPair<int, int> t(1, 4);
	TPair<int, int> t1(10, 10);

	t1 -= t;

	EXPECT_EQ(t1.first(), 9);
	EXPECT_EQ(t1.second(), 6);
}

TEST(TestPairLib, CheckOperatorFractionRavno) {
	TPair<double, double> t(1, 5);
	TPair<double, double> t1(10, 10);

	t1 /= t;

	EXPECT_DOUBLE_EQ(t1.first(), 10.0);
	EXPECT_DOUBLE_EQ(t1.second(), 2.0);
}

TEST(TestPairLib, CheckOperatorMultRavno) {
	TPair<int, int> t(1, 4);
	TPair<int, int> t1(10, 10);

	t1 *= t;

	EXPECT_EQ(t1.first(), 10);
	EXPECT_EQ(t1.second(), 40);
}

TEST(TestPairLib, CheckOperatorPlus) {
	TPair<int, int> t(1, 4);
	TPair<int, int> t1(10, 10);

	TPair<int, int> result = t + t1;

	EXPECT_EQ(result.first(), 11);
	EXPECT_EQ(result.second(), 14);
}

TEST(TestPairLib, CheckOperatorMinus) {
	TPair<int, int> t(1, 4);
	TPair<int, int> t1(10, 10);

	TPair<int, int> result = t1 - t;

	EXPECT_EQ(result.first(), 9);
	EXPECT_EQ(result.second(), 6);
}

TEST(TestPairLib, CheckOperatorMultiply) {
	TPair<int, int> t(2, 3);
	TPair<int, int> t1(4, 5);

	TPair<int, int> result = t * t1;

	EXPECT_EQ(result.first(), 8);
	EXPECT_EQ(result.second(), 15);
}


TEST(TestPairLib, CheckOperatorFrac) {
	TPair<double, double> t(2.0, 4.0);
	TPair<double, double> t1(4.0, 2.0);

	TPair<double, double> result = t1 / t;

	EXPECT_DOUBLE_EQ(result.first(), 2.0);
	EXPECT_DOUBLE_EQ(result.second(), 0.5);
}

TEST(TestPairLib, CheckSwap) {
	TPair<int, int> t(1, 4);
	TPair<int, int> t1(10, 10);

	t.swap(t1);

	EXPECT_EQ(t.first(), 10);
	EXPECT_EQ(t.second(), 10);
	EXPECT_EQ(t1.first(), 1);
	EXPECT_EQ(t1.second(), 4);
}
