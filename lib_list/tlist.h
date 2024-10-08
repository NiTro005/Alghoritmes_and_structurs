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
     TList() = default;
     TList(const TList& list);
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


template<typename T>
TList<T>::TList<T>(const TList<T>& list) : head(list.head), last(list.last) {}

template<typename T>
TList<T>::~TList(){
    while (head != nullptr) {
        Node<T>* link = head;
        head = head->next();
        delete link;
    }
}

template<typename T>
void TList<T>::push_front(const T& value) noexcept {
    if (head == nullptr) {
        head = new TNode<T>(value);
        last = head;
    } else {
        TNode<T>* link = new TNode<T>(value, head);
        head = link;
    }
}

template<typename T>
void TList<T>::push_back(const T& value) noexcept {
    if (last == nullptr) {
        head = new TNode<T>(value);
        last = head;
    } else {
        TNode<T>* link = new TNode<T>(value);
        last->next(link);
        last = link;
    }
}

template<typename T>
void TList<T>::insert(TNode<T>* node, const T& value) {
    if (node == nullptr) {
        throw std::invalid_argument("Node pointer is nullptr");
    }
    if (node->next() == nullptr) {
        TNode<T>* newNode = new TNode<T>(value);
        node->next(newNode);
        last = newNode;
    } else {
        TNode<T>* newNode = new TNode<T>(value, node->next());
        node->next(newNode);
    }
}

template<typename T>
void TList<T>::insert(size_t pos, const T& value) {
    TNode<T>* cur = head;
    if (pos == 0) {
        push_front(value);
        return;
    }
    for (size_t i = 0; i != pos; i++) {
        cur = cur->next();
        if (cur == nullptr) { throw std::logic_error("Out of range"); }
    }
    if (cur->next() == nullptr) { 
        push_back(value); 
        return;
    }
    insert(cur, value);
}


