// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_dmassive/archive.h"

template <typename T>
class TQueue {
    TDMassive<T> _data;

 public:
    explicit TQueue(size_t size = 20);
    ~TQueue();

    inline size_t size() const noexcept;

    inline bool IsEmpty() const noexcept;
    inline bool IsFull() const noexcept;

    void push(T value);
    void pop();
    inline T top() const;
};

template <typename T>
TQueue<T>::TQueue(size_t size) : _data(size) {}

template <typename T>
inline size_t TQueue<T>::size() const noexcept {
    return _data.capacity();
}

template <typename T>
TQueue<T>::~TQueue() {}

template <typename T>
inline bool TQueue<T>::IsEmpty() const noexcept {
    return _data.empty();
}

template <typename T>
inline bool TQueue<T>::IsFull() const noexcept {
    return _data.full();
}

template<typename T>
void TQueue<T>::push(T value) {
    if (!IsFull()) {
        _data.push_back(value);
    } else {
        throw std::out_of_range("Error:Overlow stack");
    }
}

template<typename T>
inline void TQueue<T>::pop() {
    if (!IsEmpty()) {
        _data.pop_front();
    } else {
        throw std::out_of_range("Stack is empty");
    }
}

template<typename T>
inline T TQueue<T>::top() const {
    if (IsEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    return _data.data()[0];
}
