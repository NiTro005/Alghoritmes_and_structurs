// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_dmassive/archive.h"

class DSU {
    int _size;
    TDMassive<int> _parent;
    TDMassive<int> _rank;

public:
    DSU(int size = 0);
    ~DSU();
    int parent(int elem);
    void make_set(int elem);
    int find(int elem);
    void Union(int first, int second);
    void clear();
};
