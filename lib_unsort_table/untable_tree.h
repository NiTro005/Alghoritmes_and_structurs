// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <unordered_set>
#include <random>
#include <limits>

#include "../lib_binSearchTree/binSearchTree.h"
#include "../lib_pair/pair.h"
#include "../lib_itable/itable.h"

template <class Tkey, class Tval>
class TBSTable : public ITable<Tkey, Tval> {
    TBinSearchTree<TPair<Tkey, Tval>> _data;
    size_t _size = 0;

public:
    TBSTable() = default;
    explicit TBSTable(const TBinSearchTree<TPair<Tkey, Tval>>& data);
    TBSTable(const TBSTable<Tkey, Tval>& tab);
    ~TBSTable() = default;
    Tkey insert(Tval val) override;
    void insert(Tkey key, Tval val) override;
    void erase(Tkey key) override;
    Tval find(Tkey key) override;
    Tval operator[](Tkey key) override;
    TBSTable& operator=(const TBSTable<Tkey, Tval>& tab) noexcept;
};