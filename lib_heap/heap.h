// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_dmassive/archive.h"

template <class TVal>
class Heap {
    TVal* _data;
    size_t _capacity, _size;
public:
    Heap(size_t size = 0);
    Heap(size_t, const TVal*);

    inline size_t lelt(size_t index) const;
    inline size_t right(size_t index) const;
    inline size_t parent(size_t index) const;
    inline bool is_empty() const noexcept;
    void insert(TVal value) noexcept;

    void emplace(size_t index, TVal value);
    inline TVal top() const;
    TVal remove();
private:
    void max_heapify() noexcept;
    void min_heapify() noexcept;
    void sift_down(size_t) noexcept;
    void sift_up(size_t) noexcept;
};
