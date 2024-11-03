// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_list/tlist.h"

template <typename T>
class LStack {
    TList<T> _list;
    size_t _capacity;
    size_t _size = 0;

 public:
     explicit LStack(size_t capacity = 20);
    ~LStack();

    inline size_t size() const noexcept;
    inline size_t capacity() const noexcept;

    inline bool IsEmpty() const noexcept;
    inline bool IsFull() const noexcept;

    void push(T value);
    void pop();
    inline T top() const;
};

template <typename T>
LStack<T>::LStack(size_t capacity): _capacity(capacity) {}

template <typename T>
inline size_t LStack<T>::size() const noexcept {
    return _size;
}

template<typename T>
inline size_t LStack<T>::capacity() const noexcept {
    return _capacity;
}

template <typename T>
LStack<T>::~LStack() {}

template <typename T>
inline bool LStack<T>:: IsEmpty() const noexcept {
    return _list.isEmpty();
}

template<typename T>
inline bool LStack<T>::IsFull() const noexcept
{
    return _size >= _capacity;
}

template<typename T>
void LStack<T>::push(T value) {
    if (!IsFull()) {
         _list.push_front(value);
         _size++;
    } else {
        throw std::out_of_range("Error:Overlow stack");
    }
}

template<typename T>
inline void LStack<T>::pop() {
    if (!IsEmpty()) {
        _list.pop_front();
        _size--;
    } else {
        throw std::out_of_range("Stack is empty");
    }
}

template<typename T>
inline T LStack<T>::top() const {
    if (IsEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    return _list.head->value();
}
