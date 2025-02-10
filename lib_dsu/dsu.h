// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>

class DSU {
    int _size;
    int* _parent;
    int* _rank;

public:
    DSU(int size = 0);
    ~DSU();
    void make_set(int elem);
    int find(int elem);
    void Union(int first, int second);
    void clear();
};