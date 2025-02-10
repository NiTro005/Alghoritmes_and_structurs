// Copyright 2024 Kita Trofimov
#include "../lib_dsu/dsu.h"

DSU::DSU(int size): _size(size), _parent(size), _rank(size, 0) {}
DSU::~DSU() {}

int DSU::parent(int elem) {
    return _parent[elem - 1] + 1;
}

void DSU::make_set(int elem) {
    if (elem > _size || elem <= 0) {
        throw std::logic_error("incorrect element\n");
    }
    elem--;
    _parent[elem] = elem;
}

int DSU::find(int elem) {
    if (elem <= 0 || elem > _size) {
        throw std::logic_error("Incorrect element\n");
    }
    elem--;
    if (_parent[elem] != elem) { _parent[elem] = find(_parent[elem]); }
    return _parent[elem];
}

void DSU::Union(int first, int second) {
    int first_parent = find(first);
    int second_parent = find(second);
    _parent[second_parent] = first_parent;
}

void DSU::clear() {
    _parent.clear();
    _rank.clear();
    _size = 0;
}
