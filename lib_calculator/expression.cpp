// Copyright 2024 Kita Trofimov
#include "expression.h"
#include "lexems.h"

bool is_number(char symbol) {
    return symbol >= '0' && symbol <= '9';
}

bool is_alpha(char symbol) {
    return symbol >= 'a' && symbol <= 'z';
}

Lexem::Lexem(std::string name, LexemType type) : _name(name), _type(type) {}

void Lexem::set_name(std::string name) {
    _name = name;
}

void Lexem::set_type(LexemType type) {
    _type = type;
}

std::string Lexem::name() const {
    return _name;
}

LexemType Lexem::type() const {
    return _type;
}

std::ostream& operator<<(std::ostream& out, const Lexem& lexem) {
    out << lexem._name;
    return out;
}

Expression::Expression(std::string exp) {
    parse(exp);
    check();
}

void Expression::print() {
    for (auto it = _expression.begin(); it != _expression.end(); it++) {
        std::cout << *it << " ";
    }
}


void Expression::parse(std::string exp) {
    int curr_pos = 0;
    while (curr_pos < exp.size()) {
        if (exp[curr_pos] == '(' || exp[curr_pos] == ')') {
            parse_bracket(exp, curr_pos);
        } else if (is_alpha(exp[curr_pos])) {
            parse_variable_or_function(exp, curr_pos);
        } else if (exp[curr_pos] == '+' || exp[curr_pos] == '-'
            || exp[curr_pos] == '*' || exp[curr_pos] == '/'
            || exp[curr_pos] == '^') {
            parse_operation(exp, curr_pos);
        } else if (is_number(exp[curr_pos])) {
            parse_number(exp, curr_pos);
        } else {
            curr_pos++;
        }
    }
}

void Expression::parse_bracket(std::string& exp, int& curr_pos) {
    Bracket new_lexem(exp.substr(curr_pos, 1));
    _expression.push_back(new_lexem);
    curr_pos++;
}

void Expression::parse_variable_or_function
(std::string& exp, int& curr_pos) {
    int start_pos = curr_pos;
    while (curr_pos < exp.size() && (is_alpha(exp[curr_pos])
        || is_number(exp[curr_pos]))) {
        curr_pos++;
    }
    std::string token = exp.substr(start_pos, curr_pos - start_pos);
    if (token == "sin" || token == "cos"
        || token == "tg" || token == "ctg") {
        Function new_lexem(token);
        _expression.push_back(new_lexem);
    } else {
        Variable new_lexem(token);
        _expression.push_back(new_lexem);
    }
}

void Expression::parse_operation(std::string& exp, int& curr_pos) {
    Operation new_lexem(exp.substr(curr_pos, 1));
    _expression.push_back(new_lexem);
    curr_pos++;
}

void Expression::parse_number(std::string& exp, int& curr_pos) {
    int start_pos = curr_pos;
    while (curr_pos < exp.size() && is_number(exp[curr_pos])) {
        curr_pos++;
    }
    if (curr_pos < exp.size() && exp[curr_pos] == '.') {
        curr_pos++;
        while (curr_pos < exp.size() && is_number(exp[curr_pos])) {
            curr_pos++;
        }
        FloatConst new_lexem(exp.substr(start_pos, curr_pos - start_pos));
        _expression.push_back(new_lexem);
    } else {
        IntConst new_lexem(exp.substr(start_pos, curr_pos - start_pos));
        _expression.push_back(new_lexem);
    }
}

void Expression::check() {
    int bracket_count = 0;
    bool last_was_operation = false;
    bool last_was_function = false;
    bool first_lexem = true;

    for (auto it = _expression.begin(); it != _expression.end(); ++it) {
        if ((*it).type() == LexemType::BRACKET) {
            if ((*it).name() == "(") {
                bracket_count++;
            } else if ((*it).name() == ")") {
                bracket_count--;
            }
            last_was_operation = false;
            last_was_function = false;
        } else if ((*it).type() == LexemType::OPERATION) {
            if (first_lexem || last_was_operation || last_was_function) {
                throw std::runtime_error
                ("Invalid expression: consecutive operations or function followed by operation");
            }
            last_was_operation = true;
            last_was_function = false;
        } else if ((*it).type() == LexemType::FUNCTION) {
            if (last_was_operation || last_was_function) {
                throw std::runtime_error
                ("Invalid expression: consecutive functions or operation followed by function");
            }
            last_was_operation = false;
            last_was_function = true;
        } else {
            last_was_operation = false;
            last_was_function = false;
        }
        first_lexem = false;
    }

    if (bracket_count != 0) {
        throw std::runtime_error("Invalid expression: unbalanced brackets");
    }

    if (last_was_operation) {
        throw std::runtime_error("Invalid expression: ends with an operation");
    }

    if (_expression.isEmpty()) {
        throw std::runtime_error("Invalid expression: empty expression");
    }
}
