// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
template<class T>
class TBinSearchTree;
template<class T>
class TBinNode {
    T value;
    TBinNode<T>* left;
    TBinNode<T>* right;

 public:
    TBinNode() = default;
    explicit TBinNode(T value, TBinNode<T>* left = nullptr,
        TBinNode<T>* right = nullptr);
    TBinNode(const TBinNode<T>& node);
    T get_value();
    TBinNode<T>* get_left();
    TBinNode<T>* get_right();

    TBinNode<T>& operator=(const TBinNode<T>& nod);
    bool operator==(T value);
    friend class TBinSearchTree<T>;
};

template<class T>
TBinNode<T>::TBinNode(T value, TBinNode<T>* left, TBinNode<T>* right):
value(value), left(left), right(right) {}

template<class T>
TBinNode<T>::TBinNode(const TBinNode<T>& node):
value(node.value), left(node.left), right(node.right) {}

template<class T>
inline T TBinNode<T>::get_value() {
    return value;
}

template<class T>
inline TBinNode<T>* TBinNode<T>::get_left() {
    return left;
}

template<class T>
inline TBinNode<T>* TBinNode<T>::get_right() {
    return right;
}

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
