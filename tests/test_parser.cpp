// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include "../lib_string/cstring.h"
#include "../lib_stack/stack.h"
#include "../lib_parser/parser.h"

#include "../lib_list/tlist.h"
#include "../lib_list/tnode.h"


template <typename T>
TList<T>* createList(int size) {
    TList<T>* list = new TList<T>();
    for (int i = 0; i < size; ++i) {
        list->push_back(i);
    }
    return list;
}

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

TEST(ListCycle, Rabbit_and_turtle_function) {
    TList<int>* list = createList<int>(20);
    EXPECT_FALSE(RabbitTurtleCycleList(*list));

    list->last->next(list->head->next());

    EXPECT_TRUE(RabbitTurtleCycleList(*list));
}

TEST(ListCycle, UpheavalPointer_function) {
    CicleErr<int> cicle;
    TList<int>* list = createList<int>(20);
    list->last->next(list->head->next());
    cicle = UpheavalPointerCycleList(*list);
    EXPECT_TRUE(cicle.has_cicle);
    EXPECT_EQ(cicle.index_err, 1);
}
