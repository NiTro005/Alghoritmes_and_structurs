// Copyright 2024 Kita Trofimov
#pragma once
#include "../lib_string/cstring.h"
#include "../lib_stack/stack.h"
#include "../lib_list/tlist.h"
#include "../lib_list/tnode.h"
bool IsCorrect(const CString& str);
template<typename T>
bool RabbitTurtleCycleList(const TList<T>& list);
template bool RabbitTurtleCycleList<int>(const TList<int>& list);

template <class T>
void link_lists(TList<T>& first, TList<T>& sec) {  // NOLINT(runtime/references)
    auto s = sec.begin();
    auto f = first.begin();
    TNode<T>* cur = first.head;
    while (f != first.end() && s != sec.end()) {
        if (*f < *s) {
            cur = f.getNode();
            f++;
        } else {
            first.insert(cur, *s);
            s++;
        }
    }
    while (s != sec.end()) {
        first.push_back(*s);
        s++;
    }
}


template<typename T>
struct CicleErr {
    bool has_cicle;
    size_t index_err;

    CicleErr() = default;

    CicleErr<T>& operator=(const CicleErr<T>& other) {
        if (this != &other) {
            has_cicle = other.has_cicle;
            index_err = other.index_err;
        }
        return *this;
    }
};

template<typename T>
CicleErr<T> UpheavalPointerCycleList
(TList<T>& list);  // NOLINT(runtime/references)
template CicleErr<int> UpheavalPointerCycleList
<int>(TList<int>& list);  // NOLINT(runtime/references)
