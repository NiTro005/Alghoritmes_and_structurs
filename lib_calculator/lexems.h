// Copyright 2024 Kita Trofimov
#pragma once

#include <string>
#include <cmath>
#include "expression.h"

enum TypeBrackets { open, close};

class FloatConst : public Lexem {
    float _value;
 public:
    FloatConst(std::string exp) : Lexem(exp, FLOAT_CONST) {
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
    int _value;
public:
    IntConst(std::string name) : Lexem(name, INT_CONST) {
        _value = std::stoi(name);
    }

    int value() const { return _value; }
};

class Bracket : public Lexem {
    TypeBrackets type;
    int priority;
public:
    Bracket(std::string name) : Lexem(name, BRACKET), priority(0) {
        if (name[0] == '(') {
            type = TypeBrackets::open;
        } else {
            type = TypeBrackets::close;
        }
    }
    void setPriority(int priority) { this->priority = priority; }
};

class Variable : public Lexem {
    int value;
public:
    Variable(std::string name) : Lexem(name, VARIABLE), value(0) {}
    void setValue(int value) { this->value = value; }
};

class Operation : public Lexem {
    int priority;
public:
    Operation(std::string name) : Lexem(name, OPERATION), priority(0) {}
    void setPriority(int priority) { this->priority = priority; }
};

class Function : public Lexem {
    int priority;
public:
    Function(std::string name) : Lexem(name, FUNCTION), priority(0) {}
    void setPriority(int priority) { this->priority = priority; }
};
