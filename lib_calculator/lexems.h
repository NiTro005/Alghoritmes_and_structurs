// Copyright 2024 Kita Trofimov
#pragma once

#include <string>
#include <cmath>
#include "../lib_calculator/expression.h"

enum TypeBrackets {
    OPEN,
    CLOSE
};

class FloatConst : public Lexem {
 public:
    float _value;
    explicit FloatConst(std::string exp) : Lexem(exp, FLOAT_CONST) {
        int curr_pos = 0;
        float result = 0;
        while (is_number(exp[curr_pos])) {
            result = result * 10 + (exp[curr_pos] - '0');
            curr_pos++;
        }
        if (exp[curr_pos] == '.') {
            curr_pos++;
            float float_part = 0.0;
            int accuracy = 0;
            while (is_number(exp[curr_pos])) {
                float_part = float_part * 10 + (exp[curr_pos] - '0');
                curr_pos++;
                accuracy++;
            }
            result += float_part * pow(10, -accuracy);
        }
        _value = result;
    }
};

class IntConst : public Lexem {
 public:
    int _value;

    explicit IntConst(std::string name) : Lexem(name, INT_CONST) {
        _value = std::stoi(name);
    }

    int value() const { return _value; }
};

class Bracket : public Lexem {
 public:
    TypeBrackets typebracket;

    explicit Bracket(std::string name) : Lexem(name, BRACKET) {
        if (name[0] == '(') {
            typebracket = TypeBrackets::OPEN;
        } else {
            typebracket = TypeBrackets::CLOSE;
        }
        _priority = 5;
    }
};

class Variable : public Lexem {
 public:
     int _value;

    explicit Variable(std::string name) : Lexem(name, VARIABLE), _value(0) {}
    void setValue(int value) { this->_value = value; }
};

class Operation : public Lexem {
 public:
    explicit Operation(std::string name) : Lexem(name, OPERATION) {
        if (name == "+" ||name == "-") _priority = 4;
        if (name == "*" || name == "/") _priority = 3;
        if (name == "^") _priority = 2;
    }
};

class Function : public Lexem {
 public:
    explicit Function(std::string name) : Lexem(name, FUNCTION) {
        _priority = 1;
    }
};
