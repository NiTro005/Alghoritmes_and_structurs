// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>

template <typename T>
class TNode {
    T _value;
    TNode<T>* pnext;
public:
    TNode(T value, TNode* nod = nullptr);
    TNode(const TNode& nod);

    TNode<T>* next();
    void next(TNode<T>* nod);
    T value();

    TNode<T>& operator=(const TNode& nod);
    bool operator==(T value);
};

template <typename T>
TNode<T>::TNode(T value, TNode* nod) : _value(value), pnext(nod) {}

template <typename T>
TNode<T>::TNode(const TNode& nod) : _value(nod._value), pnext(nod.pnext) {}

template <typename T>
inline TNode<T>* TNode<T>::next() { return pnext; }

template<typename T>
inline void TNode<T>::next(TNode<T>* nod){ pnext = nod; }

template <typename T>
inline T TNode<T>:: value() { return _value; }

template <typename T>
TNode<T>& TNode<T>:: operator=(const TNode<T>& nod) {
    _value = nod._value;
    pnext = nod.pnext;
    return *this;
}

template <typename T>
inline bool TNode<T>:: operator==(T value) { return _value == value; }
