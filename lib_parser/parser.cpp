// Copyright 2024 Kita Trofimov
#include "../lib_string/cstring.h"
#include "../lib_stack/stack.h"
#include "../lib_parser/parser.h"

#include "../lib_list/tlist.h"
#include "../lib_list/tnode.h"

bool IsCorrect(const CString& str) {
    TStack<char> stack(str.size());
    char s1 = ' ';
    for (size_t i = 0; i < str.size(); i++) {
        char s = str[i];
        if (s == '(' || s == '{' || s == '[' || (s == '|' && s1 != '|')) {
            stack.push(s);
            if (s == '|') { s1 = s; }
        } else if (s == ')' || s == '}' || s == ']' || s == '|') {
            if (stack.IsEmpty()) {
                throw std::out_of_range("No bracket in stack");
            }
            char top = stack.top();
            if ((s == ')' && top == '(') ||
                (s == '}' && top == '{') ||
                (s == ']' && top == '[') ||
                (s == '|' && top == '|')) {
                stack.pop();
                s1 = ' ';
            } else {
                throw std::logic_error("wrong bracket");
            }
        } else if (!(('0' <= s && s <= '9') || ('A' <= s && s <= 'Z') ||
            ('a' <= s && s <= 'z') || s == '*' ||
            s == '+' || s == '-' || s == '/') || s == ' ') {
            throw std::logic_error("Unexpscted symbol");
        }
    }
    if (!stack.IsEmpty()) {
        throw std::logic_error("Stack not empty");
    }
    return true;
}

template<typename T>
bool RabbitTurtleCycleList(const TList<T>& list) {
    TNode<T>* rab = list->head;
    TNode<T>* turt = list->head;
    bool noexit = true;
    while ((rab->next() || turt->next()) != last){
        rab = rab->next()->next();
        turt = turt-> next();
        if (rab->next() == turt->next()) {
            return true
        }
    }
    return false;
}
