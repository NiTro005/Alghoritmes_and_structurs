// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include "lexems.h"


TEST(CalculatorTest, CheckValidExpression) {
    ASSERT_NO_THROW(Expression exp("3 + 5 * (2 - 1)"));
}

TEST(CalculatorTest, CheckUnbalancedBrackets) {
    ASSERT_THROW(Expression exp("3 + 5 * (2 - 1"), std::runtime_error);
}

TEST(CalculatorTest, CheckEndsWithOperation) {
    ASSERT_THROW(Expression exp("3 + 5 * (2 - 1) +"), std::runtime_error);
}

TEST(CalculatorTest, CheckConsecutiveOperations) {
    ASSERT_THROW(Expression exp("3 + + 5 * (2 - 1)"), std::runtime_error);
}

TEST(CalculatorTest, CheckConsecutiveFunctions) {
    ASSERT_THROW(Expression exp("sin cos(x)"), std::runtime_error);
}

TEST(CalculatorTest, CheckOperationAfterFunction) {
    ASSERT_THROW(Expression exp("sin(x) + cos(x)"), std::runtime_error);
}

TEST(CalculatorTest, CheckFunctionAfterOperation) {
    ASSERT_THROW(Expression exp("3 + sin(x)"), std::runtime_error);
}

TEST(CalculatorTest, CheckEmptyExpression) {
    ASSERT_THROW(Expression exp(""), std::runtime_error);
}

TEST(CalculatorTest, CheckStartsWithOperation) {
    ASSERT_THROW(Expression exp("+ 3 + 5 * (2 - 1)"), std::runtime_error);
}

TEST(CalculatorTest, CheckStartsWithClosingBracket) {
    ASSERT_THROW(Expression exp(") 3 + 5 * (2 - 1)"), std::runtime_error);
}
