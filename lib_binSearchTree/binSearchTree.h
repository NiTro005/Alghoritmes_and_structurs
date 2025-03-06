// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <algorithm>
#include "../lib_binSearchTree/binNode.h"

template<class T>
class TBinSearchTree {
    TBinNode<T>* _head;

 public:
    TBinSearchTree() = default;
    ~TBinSearchTree();

    TBinNode<T>* search(T val) const noexcept;
    TBinNode<T>* insert(T val);
    void erase(T val);
    T min(TBinNode<T>*& node);
    void clear() noexcept;
    void clear(TBinNode<T>* node) noexcept;
    void print() const noexcept;
};

template<class T>
TBinSearchTree<T>::~TBinSearchTree() {
    clear();
}

template<class T>
TBinNode<T>* TBinSearchTree<T>::search(T val) const noexcept {
    TBinNode<T>* cur = head;
    TBinNode<T>* pred = nullptr;

    while (cur != nullptr) {
        pred = cur;
        if (cur->value < val) {
            cur = cur->right;
        } else if (cur->value > val) {
            cur = cur->left;
        } else {
            return cur;
        }
    }
    return pred;
}

template<class T>
TBinNode<T>* TBinSearchTree<T>::insert(T val) {
    TBinNode<T>* pred = search(val);
    TBinNode<T>* new_node = new TBinNode<T>(val);

    if (pred == nullptr) {
        head = new_node;
        return new_node;
    }

    if (pred->value == val) {
        throw std::logic_error("This value is busy");
    } else if (pred->value < val) {
        pred->right = new_node;
    } else {
        pred->left = new_node;
    }
    return new_node;
}

template<class T>
void TBinSearchTree<T>::erase(T val) {
    TBinNode<T>* node = search(val);
    if (node->value != val) {
        throw std::logic_error("No value");
    }
    if (node->left != nullptr) {
        T value = min(node);
        node->value = value;
    }
    if (node->left == nullptr && node->right != nullptr) {
        node->value = node->right->value;
        delete node->right;
        node->right = nullptr;
    }
}

template<class T>
T TBinSearchTree<T>::min(TBinNode<T>*& node) {
    TBinNode<T>* cur = node;
    TBinNode<T>* prev = nullptr;

    while (cur->left != nullptr) {
        prev = cur;
        cur = cur->left;
    }
    T value = cur->value;

    if (prev == nullptr) {
        node = cur->right;
    } else {
        prev->left = cur->right;
    }

    delete cur;
    return value;
}


template<class T>
void TBinSearchTree<T>::clear() noexcept {
    clear(head);
    head = nullptr;
}

template<class T>
void TBinSearchTree<T>::clear(TBinNode<T>* node) noexcept {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}
