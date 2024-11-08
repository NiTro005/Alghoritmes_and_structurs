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

template<typename T>
struct CicleErr {
    bool has_cicle;
    TNode<T>* node = nullptr;

    CicleErr() = default;

    CicleErr<T>& operator=(const CicleErr<T>& other) {
        if (this != &other) {
            has_cicle = other.has_cicle;
            node = other.node;
        }
        return *this;
    }
};

template<typename T>
CicleErr<T> UpheavalPointerCycleList(const TList<T>& list);
template CicleErr<int> UpheavalPointerCycleList<int>(const TList<int>& list);
