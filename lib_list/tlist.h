// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <utility>
#include "../lib_list/tnode.h"

template <typename T>
class TList {
    TNode<T>* head;
    TNode<T>* last;
 public:
     TList();
     TList(const TNode& node);
     ~TList();

     void push_front(const T& value) noexcept;
     void push_back(const T& value) noexcept;
     void insert(TNode<T>* node, const T& value);
     void insert(size_t pos, const T& value);

     TNode<T>* find(const T& value) const noexcept;
     bool isEmpty();

     void pop_front();
     void pop_back();
     void erase(TNode<T>* node);
     void erase(size_t pos);

     void replace(TNode<T>* node);
     void replace(size_t pos);

     void asort(TList<T>& list) noexcept;
};
