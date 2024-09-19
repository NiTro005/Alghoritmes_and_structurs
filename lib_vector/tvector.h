// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_dmassive/archive.h"

template <typename T>
class TVector {
    TDMassive<T> _data;
    size_t _start_index;

 public:
    TVector();
    TVector(const TVector& vec);
    TVector(const T* arr, size_t n, size_t start_index = 0);
    TVector(size_t n, T value, size_t start_index = 0);
    TVector(const TVector& vec, size_t pos, size_t n, size_t start_index = 0);
    explicit TVector(size_t n, size_t start_index = 0);
    ~TVector();

    void print() const noexcept;

    inline bool empty() const noexcept;
    inline bool full() const noexcept;

    size_t size() const noexcept;
    size_t start_index() const noexcept;
    const T* data() const;

    void swap(TVector& vec);

    TVector& assign(const TVector& vec);

    void clear();
    void resize(size_t n, T value = T());
    void reserve(size_t n = 15);

    void push_back(T value);
    void pop_back();
    void push_front(T value);
    void pop_front();

    TVector& insert(const T* arr, size_t n, size_t pos);
    TVector& insert(T value, size_t pos);

    TVector& replace(size_t pos, T new_value);

    TVector& erase(size_t pos, size_t n);
    TVector& remove_all(T value);
    TVector& remove_first(T value);
    TVector& remove_last(T value);
    TVector& remove_by_index(size_t pos);

    size_t* find_all(T value) const noexcept;
    size_t find_first(T value) const;
    size_t find_last(T value) const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    TVector operator+(const TVector& vec) const;
    TVector operator-(const TVector& vec) const;
    TVector operator*(T scalar) const;
    TVector operator+=(const TVector& vec) const;
    TVector operator-=(const TVector& vec) const;
    TVector operator*=(T scalar) const;
    bool operator==(const TVector& vec) const;
    bool operator!=(const TVector& vec) const;
};

template <typename T>
TVector<T>::TVector(): _start_index(0) {}

template <typename T>
TVector<T>:: TVector(const TVector& vec) : _data(vec._data), _start_index(vec._start_index) {}

template <typename T>
TVector<T>::TVector(const T* arr, size_t n, size_t start_index) : _data(arr, n), _start_index(start_index) {}

template <typename T>
TVector<T>::TVector(size_t n, T value, size_t start_index) : _data(n, value), _start_index(start_index) {}

template <typename T>
TVector<T>::TVector(const TVector& vec, size_t pos, size_t n, size_t start_index) : _data(other._data, pos, n), _start_index(start_index) {}

template <typename T>
TVector<T>::TVector(size_t n, size_t start_index) : _data(n), _start_index(start_index) {}

template <typename T>
TVector<T>::~TVector() {}

template <typename T>
void TVector<T>::print() const noexcept {
    for (size_t i = _start_index; i < _data.size(); ++i) {
        std::cout << _data[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
inline bool TVector<T>::empty() const noexcept {
    return _data.empty();
}

template <typename T>
inline bool TVector<T>::full() const noexcept {
    return _data.full();
}

template <typename T>
size_t TVector<T>::size() const noexcept {
    return _data.size() - _start_index;
}

template <typename T>
size_t TVector<T>::start_index() const noexcept {
    return _start_index;
}