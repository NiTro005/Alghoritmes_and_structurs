// Copyright 2024 Kita Trofimov
#include "expression.h"
#include "lexems.h"

bool is_number(char symbol) {
    return symbol >= '0' && symbol <= '9';
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
    delete_spaces(&exp);
    parse(exp);
}

void Expression::print() {
    for (auto it = _expression.begin(); it != _expression.end(); it++) {
        std::cout << *it << " ";
    }
}

void Expression::delete_spaces(std::string* exp) {
    // Реализация удаления пробелов
}

void Expression::parse(std::string exp) {
    int curr_pos = 0;
    if (is_number(exp[curr_pos])) {
        int start_pos = curr_pos;
        while (is_number(exp[curr_pos])) {
            curr_pos++;
        }
        if (exp[curr_pos] == '.') {
            curr_pos++;
            while (is_number(exp[curr_pos])) {
                curr_pos++;
            }
            FloatConst new_lexem(exp.substr(start_pos, curr_pos - start_pos));
            _expression.push_back(new_lexem);
        }
        else {
            // IntConst new_lexem(exp.substr(start_pos, curr_pos - start_pos));
        }
    }
}
