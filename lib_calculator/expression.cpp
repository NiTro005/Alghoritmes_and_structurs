// Copyright 2024 Kita Trofimov
#include <iostream>
#include <string>
#include "../lib_calculator/expression.h"
#include "../lib_calculator/lexems.h"

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

int Lexem::priority() const {
    return _priority;
}

std::ostream& operator<<(std::ostream& out, const Lexem& lexem) {
    out << lexem._name;
    return out;
}

Expression::Expression(std::string exp) {
    parse(exp);
    check();
}

void Expression::set_vars_values(std::string var, int value) {
    for (auto lex : _expression) {
        if (lex->type() == VARIABLE && lex->name() == var) {
            Variable* variable = static_cast<Variable*>(lex);
            variable->setValue(value);
        }
    }
}

double Expression::calculate() {
    build_polish_record();
    TStack<float> values;
    for (auto lex : polish_record) {
        if (lex->type() == INT_CONST) {
            IntConst* int_const = static_cast<IntConst*>(lex);
            values.push(int_const->value());
        } else if (lex->type() == FLOAT_CONST) {
            FloatConst* float_const = static_cast<FloatConst*>(lex);
            values.push(float_const->_value);
        } else if (lex->type() == VARIABLE) {
            Variable* var = static_cast<Variable*>(lex);
            values.push(var->_value);
        } else if (lex->type() == OPERATION) {
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            if (lex->name() == "+") {
                values.push(a + b);
            } else if (lex->name() == "-") {
                values.push(a - b);
            } else if (lex->name() == "*") {
                values.push(a * b);
            } else if (lex->name() == "/") {
                values.push(a / b);
            } else if (lex->name() == "^") {
                values.push(pow(a, b));
            }
        } else if (lex->type() == FUNCTION) {
            double a = values.top(); values.pop();
            if (lex->name() == "sin") {
                values.push(sin(a));
            } else if (lex->name() == "cos") {
                values.push(cos(a));
            } else if (lex->name() == "tg") {
                values.push(tan(a));
            } else if (lex->name() == "ctg") {
                values.push(1 / tan(a));
            }
        }
    }
    return values.top();
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

void Expression::parse_bracket(const std::string& exp, int& curr_pos) {
    Bracket* new_lexem = new Bracket(exp.substr(curr_pos, 1));
    _expression.push_back(new_lexem);
    curr_pos++;
}

void Expression::parse_variable_or_function
(const std::string& exp, int& curr_pos) {
    int start_pos = curr_pos;
    while (curr_pos < exp.size() && (is_alpha(exp[curr_pos])
        || is_number(exp[curr_pos]))) {
        curr_pos++;
    }
    std::string token = exp.substr(start_pos, curr_pos - start_pos);
    if (token == "sin" || token == "cos"
        || token == "tg" || token == "ctg") {
        Function* new_lexem = new Function(token);
        _expression.push_back(new_lexem);
    } else {
        Variable* new_lexem = new Variable(token);
        _expression.push_back(new_lexem);
    }
}

void Expression::parse_operation(const std::string& exp, int& curr_pos) {
    Operation* new_lexem = new Operation(exp.substr(curr_pos, 1));
    _expression.push_back(new_lexem);
    curr_pos++;
}

void Expression::parse_number(const std::string& exp, int& curr_pos) {
    int start_pos = curr_pos;
    while (curr_pos < exp.size() && is_number(exp[curr_pos])) {
        curr_pos++;
    }
    if (curr_pos < exp.size() && exp[curr_pos] == '.') {
        curr_pos++;
        while (curr_pos < exp.size() && is_number(exp[curr_pos])) {
            curr_pos++;
        }
        FloatConst* new_lexem =
            new FloatConst(exp.substr(start_pos, curr_pos - start_pos));
        _expression.push_back(new_lexem);
    } else {
        IntConst* new_lexem =
            new IntConst(exp.substr(start_pos, curr_pos - start_pos));
        _expression.push_back(new_lexem);
    }
}

void Expression::build_polish_record() {
    TStack<Lexem*> operations;
    for (auto lex : _expression) {
        if (lex->type() == VARIABLE ||
            lex->type() == INT_CONST || lex->type() == FLOAT_CONST) {
            polish_record.push_back(lex);
        } else {
            if (lex->type() == BRACKET) {
                Bracket* bracket = static_cast<Bracket*>(lex);
                if (bracket->typebracket == OPEN) {
                    operations.push(lex);
                } else {
                    while (operations.top()->type() != BRACKET) {
                        polish_record.push_back(operations.top());
                        operations.pop();
                    }
                    operations.pop();
                    if (operations.top()->type() == FUNCTION) {
                        polish_record.push_back(operations.top());
                        operations.pop();
                    }
                }
            } else {
                if (operations.IsEmpty() || lex->priority() <
                    operations.top()->priority()) {
                    operations.push(lex);
                } else if (operations.IsEmpty() ||
                    lex->priority() == operations.top()->priority()) {
                    polish_record.push_back(operations.top());
                    operations.pop();
                    operations.push(lex);
                } else {
                    while (!operations.IsEmpty() &&
                        operations.top()->priority() <= lex->priority()) {
                        polish_record.push_back(operations.top());
                        operations.pop();
                    }
                    operations.push(lex);
                }
            }
        }
    }
    while (!operations.IsEmpty()) {
        polish_record.push_back(operations.top());
        operations.pop();
    }
}

void Expression::check() {
    int bracket_count = 0;
    bool last_was_operation = false;
    bool last_was_function = false;
    bool first_lexem = true;

    for (auto it = _expression.begin(); it != _expression.end(); ++it) {
        if ((*it)->type() == LexemType::BRACKET) {
            if ((*it)->name() == "(") {
                bracket_count++;
                if (last_was_function) {
                    last_was_function = false;
                }
            } else if ((*it)->name() == ")") {
                bracket_count--;
            }
            last_was_operation = false;
        } else if ((*it)->type() == LexemType::OPERATION) {
            if (first_lexem || last_was_operation) {
                throw std::runtime_error
                ("Invalid expression: consecutive operations");
            }
            last_was_operation = true;
            last_was_function = false;
        } else if ((*it)->type() == LexemType::FUNCTION) {
            if (last_was_function) {
                throw std::runtime_error
                ("Invalid expression: function must" \
                    "be followed by an opening bracket");
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
        throw std::runtime_error
        ("Invalid expression: unbalanced brackets");
    }

    if (last_was_operation) {
        throw std::runtime_error
        ("Invalid expression: ends with an operation");
    }

    if (last_was_function) {
        throw std::runtime_error
        ("Invalid expression: function must be followed by an opening bracket");
    }

    if (_expression.isEmpty()) {
        throw std::runtime_error
        ("Invalid expression: empty expression");
    }
}
