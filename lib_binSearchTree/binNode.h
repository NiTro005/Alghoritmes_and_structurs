// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>

template<class T>
class TBinNode {
 public:
    T value;
    TBinNode<T>* left, right;

    TBinNode() = default;
    TBinNode(T value, TBinNode<T>* left = nullptr, TBinNode<T>* right = nullptr);
    TBinNode(const TBinNode<T>& node);

    TBinNode<T>& operator=(const TBinNode<T>& nod);
    bool operator==(T value);
};

template<class T>
TBinNode<T>::TBinNode(T value, TBinNode<T>* left, TBinNode<T>* right):
value(value), left(left), right(right) {}

template<class T>
TBinNode<T>::TBinNode(const TBinNode<T>& node):
value(node.value), left(node.left), right(node.right) {}

template<class T>
TBinNode<T>& TBinNode<T>::operator=(const TBinNode<T>& nod) {
    value = nod.value;
    left = nod.left;
    right = nod.right;
    return this;
}

template<class T>
inline bool TBinNode<T>::operator==(T value) {
    return this->value = value;
}
