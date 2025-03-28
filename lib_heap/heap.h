// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_dmassive/archive.h"

enum Type { MIN, MAX };

template <class TVal>
class Heap {
    TVal* _data;
    size_t _capacity, _size;

    bool (*_comp)(const TVal& val1, const TVal& val2);
public:
    Heap(size_t size = 0, Type type = MAX);
    Heap(size_t size, const TVal* data, Type type = MAX);

    inline size_t lelt(size_t index) const;
    inline size_t right(size_t index) const;
    inline size_t parent(size_t index) const;
    inline bool is_empty() const noexcept;
    void insert(TVal value) noexcept;

    void emplace(size_t index, TVal value);
    inline TVal top() const;
    TVal remove();
private:
    static bool less(const TVal& a, const TVal& b);
    static bool greater(const TVal& a, const TVal& b);

    void heapify() noexcept;
    void sift_down(size_t) noexcept;
    void sift_up(size_t) noexcept;
};

template<class TVal>
Heap<TVal>::Heap(size_t size, Type type) : _data(new TVal[size]),
_capacity(size), _size(0) {
    _comp = (type == MAX) ? &greater : &less;
}

template<class TVal>
inline size_t Heap<TVal>::lelt(size_t index) const {
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
inline TVal Heap<TVal>::top() const {
    return _data[0];
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
