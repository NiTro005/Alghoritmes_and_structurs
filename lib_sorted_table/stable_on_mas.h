// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_dmassive/archive.h"
#include "../lib_pair/pair.h"
#include "../lib_itable/itable.h"

template <class Tkey, class Tval>
class SortedTabOnMas : ITable {
    TDMassive<TPair<Tkey, Tval>> _data;

 public:
     SortedTabOnMas() = default;
     explicit SortedTabOnMas(const TDMassive<TPair<Tkey, Tval>>& mas);
     SortedTabOnMas(const SortedTabOnMas<Tkey, Tval>& tab);

     Tkey insert(Tval val) override;
     void insert(Tkey key, Tval val) override;
     void erase(Tkey key) override;
     Tval find(Tkey key) override;
     Tval operator[](Tkey key) override;
     SortedTabOnMas& operator=(const SortedTabOnMas<Tkey, Tval>& tab);
};
