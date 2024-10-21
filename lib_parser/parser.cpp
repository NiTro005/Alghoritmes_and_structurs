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
            if (s == '|') s1 = s;
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
    TNode<T>* rab = list.head;
    TNode<T>* turt = list.head;

    while (rab != nullptr && rab->next() != nullptr
        && turt != nullptr && turt->next() != nullptr) {
        rab = rab->next()->next();
        turt = turt->next();

        if (rab == turt) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool UpheavalPointerCycleList(const TList<T>& list) {
    TList<T> _list(list);
    TNode<T>* nod = _list.head;
    TNode<T>* next = _list.head->next();
    _list.head->next(nullptr);
    while (next != nullptr) {
        TNode<T>* prev = nod;
        nod = next;
        next = next->next();
        nod->next(prev);
        if (next == list.head) return false;
        if (next == list.last) return true;
    }
    return false;
}
