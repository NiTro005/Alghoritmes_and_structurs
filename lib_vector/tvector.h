// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_dmassive/archive.h"
#include <utility>

namespace utility {
    template<typename T>
    inline T max(T val_1, T val_2) noexcept {
        if (val_1 > val_2) {
            return val_1;
        } else {
            return val_2;
        }
    }

    template<typename T>
    inline T min(T val_1, T val_2) noexcept {
        if (val_1 < val_2) {
            return val_1;
        }
        else {
            return val_2;
        }
    }
}


template <typename T>
class TVector {
    TDMassive<T> _data;
    size_t _start_index;

 public:
    TVector();
    TVector(const TVector& vec);
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

    void push_back(T value);
    void pop_back();

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

    TVector& operator=(const TVector& vec) noexcept;
    TVector operator+(const TVector& vec) const;
    TVector operator-(const TVector& vec) const;
    TVector operator*(T scalar) const;
    TVector& operator+=(const TVector& vec) const;
    TVector& operator-=(const TVector& vec) const;
    TVector& operator*=(T scalar) const;
    bool operator==(const TVector& vec) const;
    bool operator!=(const TVector& vec) const;
};

template <typename T>
TVector<T>::TVector(): _start_index(0) {}

template <typename T>
TVector<T>:: TVector(const TVector& vec) : 
    _data(vec._data), _start_index(vec._start_index) {}

template <typename T>
TVector<T>::TVector(size_t n, size_t start_index) : 
    _data(n), _start_index(start_index) {
    _data.set_size(start_index);
}

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
    return (_data.size() - _start_index) == 0;
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

template <typename T>
const T* TVector<T>::data() const {
    return _data.data();
}

template <typename T>
void TVector<T>::swap(TVector& vec) {
    _data.swap(vec._data);
    algorithm::swap(_start_index, vec._start_index);
}

template <typename T>
TVector<T>& TVector<T>::assign(const TVector& vec) {
    _data.assign(vec._data);
    _start_index = vec._start_index;
    return *this;
}

template <typename T>
void TVector<T>::clear() {
    _data.clear();
    _start_index = 0;
}

template <typename T>
void TVector<T>::resize(size_t n, T value) {
    if (n > _data.capacity()) {
        throw std::out_of_range("out of range. capacity < size");
    }
    _data.resize(n + _start_index, value);
}

template <typename T>
void TVector<T>::push_back(T value) {
    if ((_data.size() + 1) > _data.capacity()) {
        throw std::out_of_range("out of range. capacity < size");
    }
    _data.push_back(value);
}

template <typename T>
void TVector<T>::pop_back() {
    _data.pop_back();
}

template <typename T>
TVector<T>& TVector<T>::insert(const T* arr, size_t n, size_t pos) {
    if ((_data.size() + n) > _data.capacity()) {
        throw std::out_of_range("out of range. capacity < size");
    }
    _data.insert(arr, n, pos + _start_index);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::insert(T value, size_t pos) {
    if ((_data.size() + 1) > _data.capacity()) {
        throw std::out_of_range("out of range. capacity < size");
    }
    _data.insert(value, pos + _start_index);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::replace(size_t pos, T new_value) {
    _data.replace(pos + _start_index, new_value);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::erase(size_t pos, size_t n) {
    _data.erase(pos + _start_index, n);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::remove_all(T value) {
    _data.remove_all(value);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::remove_first(T value) {
    _data.remove_first(value);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::remove_last(T value) {
    _data.remove_last(value);
    return *this;
}

template <typename T>
TVector<T>& TVector<T>::remove_by_index(size_t pos) {
    _data.remove_by_index(pos + _start_index);
    return *this;
}

template <typename T>
size_t* TVector<T>::find_all(T value) const noexcept {
    return _data.find_all(value);
}

template <typename T>
size_t TVector<T>::find_first(T value) const {
    return _data.find_first(value);
}

template <typename T>
size_t TVector<T>::find_last(T value) const {
    return _data.find_last(value);
}

template <typename T>
T& TVector<T>::operator[](size_t index) {
    return _data[index + _start_index];
}

template <typename T>
const T& TVector<T>::operator[](size_t index) const {
    return _data[index + _start_index];
}

template <typename T>
TVector<T>& TVector<T>::operator=(const TVector& vec) noexcept {
    if (this != &vec) {
        _data = vec._data;
        _start_index = vec._start_index;
    }
    return *this;
}

template <typename T>
TVector<T> TVector<T>::operator+(const TVector& vec) const {
    TVector result;
    return result;
}