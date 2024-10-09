// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <utility>
#include "../lib_list/tnode.h"

template <typename T>
class TList {
 public:
     TNode<T>* head = nullptr;
     TNode<T>* last = nullptr;

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

     void replace(TNode<T>* node, const T& value);
     void replace(size_t pos, const T& value);

     void asort(TList<T>& list) noexcept;
};


template<typename T>
TList<T>::TList<T>(const TList<T>& list) : head(list.head), last(list.last) {}

template<typename T>
TList<T>::~TList(){
    while (head != nullptr) {
        TNode<T>* link = head;
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
    TNode<T>* link = new TNode<T>(value);
    if (last == nullptr) {
        head = link;
        last = head;
    } else if (last == head) {
        head->next(link);
        last = link;
    } else {
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

template<typename T>
TNode<T>* TList<T>::find(const T& value) const noexcept {
    TNode<T>* cur(head);
    do {
        if (cur->value() == value) {
            return cur;
        }
        cur = cur->next();
    } while (cur != last);
    return nullptr;
}

template<typename T>
inline bool TList<T>::isEmpty() { return head = nullptr; }

template<typename T>
void TList<T>::pop_front() {
    if (head == nullptr) { throw std::runtime_error("List is empty"); }
    TNode<T>* temp = head;
    head = head->next();
    delete temp;
}

template<typename T>
void TList<T>::pop_back() {
    if (head == nullptr) { throw std::runtime_error("List is empty"); }
    if (head == last) {
        delete head;
        head = nullptr;
        last = nullptr;
        return;
    }
    TNode<T>* current = head;
    while (current->next() != last) {
        current = current->next();
    }
    delete last;
    last = current;
    last->next(nullptr);
}

template<typename T>
void TList<T>::erase(TNode<T>* node) {
    if (node == nullptr) {
        throw std::invalid_argument("Node pointer is nullptr");
    }
    if (node == head) { pop_front(); return; }
    if (node == last) { pop_back(); return; }
    TNode<T>* link = node->next();
    node->next(node->next()->next());
    delete link;
}

template<typename T>
void TList<T>::erase(size_t pos) {
    TNode<T>* cur = head;
    if (pos == 0) { pop_front(); return; }
    for (size_t i = 0; i != pos; i++) {
        cur = cur->next();
        if (cur == nullptr) { throw std::logic_error("Out of range"); }
    }
    if (cur->next() == nullptr) { pop_back(); return; }
    erase(cur);
}

template<typename T>
void TList<T>::replace(TNode<T>* node, const T& value) {
    if (node == nullptr) { throw std::logic_error("link is null"); }
    node->set_value(value);
}

template<typename T>
void TList<T>::replace(size_t pos, const T& value) {
    TNode<T>* cur = head;
    for (size_t i = 0; i != pos; i++) {
        cur = cur->next();
        if (cur == nullptr) { throw std::logic_error("Out of range"); }
    }
    replace(cur, value);
}