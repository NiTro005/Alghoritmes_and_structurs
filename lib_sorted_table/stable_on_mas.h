// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_dmassive/archive.h"
#include "../lib_pair/pair.h"
#include "../lib_itable/itable.h"

template <class Tkey, class Tval>
class SortedTabOnMas : ITable<Tkey, Tval> {
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

template<class Tkey, class Tval>
SortedTabOnMas<Tkey, Tval>::SortedTabOnMas
(const TDMassive<TPair<Tkey, Tval>>& mas) {
    TDMassive<TPair<Tkey, Tval>> new_mas(mas);
    for (size_t i = 0; i < new_mas.size(); i++) {
        for (size_t j = i; j > 0 && new_mas[j - 1].second() > new_mas[j].second(); j--) {
            new_mas.swap(new_mas[j - 1], new_mas[j]);
        }
    }
    _data = new_mas;
}

template<class Tkey, class Tval>
inline SortedTabOnMas<Tkey, Tval>::SortedTabOnMas
(const SortedTabOnMas<Tkey, Tval>& tab): _data(tab._data) {}

