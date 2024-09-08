
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

	EXPECT_EQ(t1.first(), 13, t1.second(), 5);
}
