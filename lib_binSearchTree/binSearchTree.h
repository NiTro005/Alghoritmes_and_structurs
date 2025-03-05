// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_binSearchTree/binNode.h"

template<class T>
class TBinSearchTree {
    TBinNode<T>* _head;

 public:
    TBinSearchTree() = default;
    ~TBinSearchTree();

    TBinNode<T>* search(T val);
    TBinNode<T>* insert(T val);
    void erase(T val);
    void clear();
    void print();
};

template<class T>
TBinNode<T>* TBinSearchTree<T>::search(T val) {
    TBinNode<T>* cur = head;
    while (cur != nullptr) {
        if (cur->value < val) {
            cur = cur->right;
        } else if (cur->value > val) {
            cur = cur->left;
        } else {
            return cur;
        }
    }
    return nullptr;
}
