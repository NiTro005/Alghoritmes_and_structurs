// Copyright 2024 Kita Trofimov
#include <gtest.h>
#include <vector>
#include <string>
#include "../lib_calculator/lexems.h"


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


TEST(CalculatorTest, CheckEmptyExpression) {
    ASSERT_THROW(Expression exp(""), std::runtime_error);
}

TEST(CalculatorTest, CheckStartsWithOperation) {
    ASSERT_THROW(Expression exp("+ 3 + 5 * (2 - 1)"), std::runtime_error);
}

TEST(CalculatorTest, CheckStartsWithClosingBracket) {
    ASSERT_THROW(Expression exp(") 3 + 5 * (2 - 1)"), std::runtime_error);
}

TEST(CalculatorTest, BuildPolishRecordValidExpression) {
    Expression exp("3 + 5 * (2 - 1)");

    exp.build_polish_record();

    std::vector<std::string> expected = { "3", "5", "2", "1", "-", "*", "+" };
    std::vector<std::string> actual;
    for (const auto& lex : exp.polish_record) {
        actual.push_back(lex->name());
    }

    ASSERT_EQ(actual, expected);
}

TEST(CalculatorTest, BuildPolishRecordFunctionExpression) {
    Expression exp("sin(x + y^2) + cos(y)");
    exp.build_polish_record();

    std::vector<std::string> expected =
    { "x", "y", "2", "^", "+", "sin", "y", "cos", "+" };
    std::vector<std::string> actual;
    for (const auto& lex : exp.polish_record) {
        actual.push_back(lex->name());
    }

    ASSERT_EQ(actual, expected);
}

TEST(CalculatorTest, BuildPolishRecordNestedBrackets) {
    Expression exp("3 + (5 * (2 - 1))");
    exp.build_polish_record();

    std::vector<std::string> expected = { "3", "5", "2", "1", "-", "*", "+" };
    std::vector<std::string> actual;
    for (const auto& lex : exp.polish_record) {
        actual.push_back(lex->name());
    }

    ASSERT_EQ(actual, expected);
}

TEST(CalculatorTest, BuildPolishRecordOperationPrecedence) {
    Expression exp("3 + 5 * 2 ^ 3");
    exp.build_polish_record();

    std::vector<std::string> expected = { "3", "5", "2", "3", "^", "*", "+" };
    std::vector<std::string> actual;
    for (const auto& lex : exp.polish_record) {
        actual.push_back(lex->name());
    }

    ASSERT_EQ(actual, expected);
}

TEST(CalculatorTest, BuildPolishRecordOperationPriority) {
    Expression exp("3 + 5 ^ 2 * 3");
    exp.build_polish_record();

    std::vector<std::string> expected = { "3", "5", "2", "^", "3", "*", "+" };
    std::vector<std::string> actual;
    for (const auto& lex : exp.polish_record) {
        actual.push_back(lex->name());
    }

    ASSERT_EQ(actual, expected);
}

TEST(CalculatorTest, CalculateValidExpression) {
    Expression exp("3 + 5 * (2 - 1)");
    double result = exp.calculate();
    ASSERT_DOUBLE_EQ(result, 8.0);
}

TEST(CalculatorTest, CalculateWithVariables) {
    Expression exp("x + y");
    exp.set_vars_values("x", 2);
    exp.set_vars_values("y", 3);
    double result = exp.calculate();
    ASSERT_DOUBLE_EQ(result, 5.0);
}

TEST(CalculatorTest, CalculateWithFunction) {
    Expression exp("sin(x) + cos(y)");
    exp.set_vars_values("x", 0);
    exp.set_vars_values("y", 0);
    double result = exp.calculate();
    ASSERT_DOUBLE_EQ(result, 1.0);
}

TEST(CalculatorTest, CalculateWithFunctionAndVariables) {
    Expression exp("sin(x) + cos(y) + z");
    exp.set_vars_values("x", 0);
    exp.set_vars_values("y", 0);
    exp.set_vars_values("z", 1);
    double result = exp.calculate();
    ASSERT_DOUBLE_EQ(result, 2.0);
}

TEST(CalculatorTest, CalculateWithOperationPrecedence) {
    Expression exp("3 + 5 * 2 ^ 3");
    double result = exp.calculate();
    ASSERT_DOUBLE_EQ(result, 43.0);
}

TEST(CalculatorTest, CalculateWithNestedBrackets) {
    Expression exp("3 + (5 * (2 - 1))");
    double result = exp.calculate();
    ASSERT_DOUBLE_EQ(result, 8.0);
}

TEST(ExpressionTest, CalculateComplexExpression) {
    Expression exp("sin(x) + cos(y) * (2 + 3) ^ (z - 1)");

    exp.set_vars_values("x", 0);
    exp.set_vars_values("y", 0);
    exp.set_vars_values("z", 2);
    double result = exp.calculate();

    ASSERT_DOUBLE_EQ(result, 5.0);
}
