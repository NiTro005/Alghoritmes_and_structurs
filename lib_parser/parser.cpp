// Copyright 2024 Kita Trofimov
#include "../lib_string/cstring.h"
#include "../lib_stack/stack.h"
#include "../lib_parser/parser.h"

#include "../lib_list/tlist.h"
#include "../lib_list/tnode.h"
#include <iostream>
#include <vector>


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
void RecoveryList(const TList<T>& list, size_t size, size_t index) {
    TList<T> _list(list);
    size_t cur_size = size;
    TNode<T>* cur = _list.head;
    TNode<T>* cur_next = cur;
    TNode<T>* cur_prev = cur;


    for (size_t i = 0; i <= size; i++) {
        cur_prev = cur;
        cur = cur_next;
        cur_next = cur_next->next();
        if (index >= i) {
            continue;
        } else if (cur == _list.last) {
            cur->next(nullptr);
        } else {
            cur->next(cur_prev);
        }
    }
}

template<typename T>
CicleErr<T> UpheavalPointerCycleList(TList<T>& _list) {
    CicleErr<T> cicle;
    TNode<T>* nod = _list.head;
    TNode<T>* next = _list.head->next();
    std::vector<TNode<T>*> find_index_err;
    size_t size = 0;
    size_t index = 0;
    bool find = true;

    while (next != nullptr) {
        TNode<T>* prev = nod;
        nod = next;
        next = next->next();
        if (std::find(find_index_err.begin(), find_index_err.end(), nod) != find_index_err.end() && find) {
            index = size;
            find = false;
        }
        find_index_err.push_back(nod);
        nod->next(prev);
        size++;
        if (next == _list.head) {
            find_index_err.clear();
            cicle.has_cicle = true;
            RecoveryList(_list, size, size - index);
            cicle.index_err = size - index;
            return cicle;
        }
        if (next == _list.last && next->next() == nullptr) {
            cicle.has_cicle = false;
            return cicle;
        }
    }
}
