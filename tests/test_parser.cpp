// Copyright 2024 Kita Trofimov
#include "../lib_string/cstring.h"
#include "../lib_stack/stack.h"
#include "../lib_parser/parser.h"
#include <gtest.h>

TEST(IsCorrectTest, CorrectString) {
    CString str("(a+b)*{c/[d-e]}");
    EXPECT_NO_THROW(IsCorrect(str));
}

TEST(IsCorrectTest, MismatchedBrackets) {
    CString str("(a+b)*{c/[d-e])");
    EXPECT_THROW(IsCorrect(str), std::logic_error);
}

TEST(IsCorrectTest, UnexpectedSymbol) {
    CString str("(a+b)*{c/[d-e]}@");
    EXPECT_THROW(IsCorrect(str), std::logic_error);
}

TEST(IsCorrectTest, MissingBrackets) {
    CString str("(a+b)*{c/[d-e]");
    EXPECT_THROW(IsCorrect(str), std::logic_error);
}

TEST(IsCorrectTest, ExtraBrackets) {
    CString str("(a+b)*{c/[d-e]})");
    EXPECT_THROW(IsCorrect(str), std::logic_error);
}

TEST(IsCorrectTest, WrongBracketOrder) {
    CString str("(a+b)*{c/[d-e]}]");
    EXPECT_THROW(IsCorrect(str), std::logic_error);
}

TEST(IsCorrectTest, WrongVerticalBar) {
    CString str("(a+b)*{c/[d-e]|");
    EXPECT_THROW(IsCorrect(str), std::logic_error);
}

TEST(IsCorrectTest, WrongVerticalBar2) {
    CString str("|a+b)*{c/[d-e]}");
    EXPECT_THROW(IsCorrect(str), std::logic_error);
}

TEST(IsCorrectTest, Wrong_brecket_in_start) {
    CString str("}|a+b)*{c/[d-e]}");
    EXPECT_THROW(IsCorrect(str), std::out_of_range);
}

TEST(IsCorrectTest, AbsoluteValue) {
    CString str("|a+b|*|a|");
    EXPECT_NO_THROW(IsCorrect(str));
}
