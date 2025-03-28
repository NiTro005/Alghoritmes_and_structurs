// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <utility>
#include "../lib_dmassive/archive.h"

enum Type { MIN, MAX };

template <class TVal>
class Heap {
    TVal* _data;
    size_t _capacity, _size;

    bool (*_comp)(const TVal& val1, const TVal& val2);

 public:
    explicit Heap(size_t size = 0, Type type = MAX);
    Heap(size_t size, const TVal* data, Type type = MAX);

    inline size_t left(size_t index) const;
    inline size_t right(size_t index) const;
    inline size_t parent(size_t index) const;
    inline bool is_empty() const noexcept;
    void insert(TVal value) noexcept;

    void emplace(size_t index, const TVal& value);
    inline TVal top() const;
    TVal remove();

 private:
    static bool less(const TVal& a, const TVal& b);
    static bool greater(const TVal& a, const TVal& b);

    void heapify() noexcept;
    void sift_down(size_t index) noexcept;
    void sift_up(size_t index) noexcept;
};

template<class TVal>
Heap<TVal>::Heap(size_t size, Type type) : _data(new TVal[size]),
_capacity(size), _size(0) {
    _comp = (type == MAX) ? &greater : &less;
}

template<class TVal>
Heap<TVal>::Heap(size_t size, const TVal* data, Type type)
    : _data(new TVal[size]), _capacity(size), _size(size),
    _comp(type == MAX ? &greater : &less) {
    for (size_t i = 0; i < size; ++i) {
        _data[i] = data[i];
    }
    heapify();
}

template<class TVal>
inline size_t Heap<TVal>::left(size_t index) const {
    return index * 2 + 1;
}

template<class TVal>
inline size_t Heap<TVal>::right(size_t index) const {
    return index * 2 + 2;
}

template<class TVal>
inline size_t Heap<TVal>::parent(size_t index) const {
    return (index - 1) / 2;
}

template<class TVal>
inline bool Heap<TVal>::is_empty() const noexcept {
    return _size == 0;
}

template<class TVal>
void Heap<TVal>::insert(TVal value) noexcept {
    _data[_size] = value;
    sift_up(_size);
    _size++;
}

template<class TVal>
void Heap<TVal>::emplace(size_t index, const TVal& value) {
    if (index >= _capacity) {
        throw std::out_of_range("Index exceeds heap capacity");
    }

    if (index < _size) {
        _data[index] = value;
        if (index > 0 && _comp(_data[index], _data[parent(index)])) {
            sift_up(index);
        } else {
            sift_down(index);
        }
    } else if (index == _size) {
        insert(value);
    } else {
        throw std::logic_error("Cannot emplace with index > current size");
    }
}

template<class TVal>
inline TVal Heap<TVal>::top() const {
    return _data[0];
}

template<class TVal>
TVal Heap<TVal>::remove() {
    if (is_empty()) throw std::logic_error("heap is empty");
    TVal value = _data[0];
    _data[0] = _data[_size - 1];
    _size--;
    if (_size > 0) sift_down(0);
    return value;
}

template<class TVal>
inline bool Heap<TVal>::less(const TVal& a, const TVal& b) {
    return a < b;
}

template<class TVal>
inline bool Heap<TVal>::greater(const TVal& a, const TVal& b) {
    return a > b;
}

template<class TVal>
void Heap<TVal>::heapify() noexcept {
    if (_size == 0) return;

    for (size_t i = parent(_size - 1); i > 0; --i) {
        sift_down(i);
    }
    sift_down(0);
}

template<class TVal>
void Heap<TVal>::sift_down(size_t index) noexcept {
    size_t extremum = index;
    size_t child;

    while (true) {
        size_t left_child = left(index);
        size_t right_child = right(index);

        if (left_child < _size && _comp(_data[left_child], _data[extremum])) {
            extremum = left_child;
        }
        if (right_child < _size && _comp(_data[right_child], _data[extremum])) {
            extremum = right_child;
        }
        if (extremum == index) {
            break;
        }

        std::swap(_data[index], _data[extremum]);
        index = extremum;
    }
}

template<class TVal>
void Heap<TVal>::sift_up(size_t index) noexcept {
    while (index > 0) {
        size_t par = parent(index);
        if (_comp(_data[index], _data[par])) {
            std::swap(_data[index], _data[par]);
            index = par;
        } else {
            break;
        }
    }
}
