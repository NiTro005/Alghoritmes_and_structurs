// Copyright 2024 Kita Trofimov
#pragma once

#include <string>
#include <cmath>
#include "expression.h"

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
