// Copyright 2024 Kita Trofimov
#pragma once

#include <iostream>
#include <string>
#include "../lib_list/tlist.h"

enum LexemType {
    BRACKET,
    VARIABLE,
    OPERATION,
    FUNCTION,
    INT_CONST,
    FLOAT_CONST
};

bool is_number(char symbol);

class Lexem {
protected:
    std::string _name;
    LexemType _type;
public:
    Lexem(std::string name, LexemType type);

    void set_name(std::string name);
    void set_type(LexemType type);

    std::string name() const;
    LexemType type() const;

    friend std::ostream& operator<<(std::ostream& out, const Lexem& lexem);
};

class Expression {
    TList<Lexem> _expression;
    // <what type?> polish_record;
public:
    Expression(std::string exp);
    //void set_vars_values();
    //void calculate();
    void print();
private:
    void delete_spaces(std::string* exp);
    void parse(std::string exp);
    void parse_bracket(std::string& exp, int& curr_pos);
    void parse_variable_or_function(std::string& exp, int& curr_pos);
    void parse_operation(std::string& exp, int& curr_pos);
    void parse_number(std::string& exp, int& curr_pos);
    //void check();
    //void build_polish_record();
};
