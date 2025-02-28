// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <unordered_set>
#include <random>
#include <limits>
#include "../lib_dmassive/archive.h"
#include "../lib_pair/pair.h"
#include "../lib_itable/itable.h"

template<class Tkey>
Tkey generate_key() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis
    (0, std::numeric_limits<Tkey>::max());
    return dis(gen);
}

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

 private:
     size_t binary_search(Tkey key);
};

template<class Tkey, class Tval>
SortedTabOnMas<Tkey, Tval>::SortedTabOnMas
(const TDMassive<TPair<Tkey, Tval>>& mas) {
    TDMassive<TPair<Tkey, Tval>> new_mas(mas);
    for (size_t i = 0; i < new_mas.size(); i++) {
        for (size_t j = i; j > 0 &&
            new_mas[j - 1].first()> new_mas[j].first(); j--) {
            algorithm::swap(new_mas[j - 1], new_mas[j]);
        }
    }
    _data = new_mas;
}

template<class Tkey, class Tval>
inline SortedTabOnMas<Tkey, Tval>::SortedTabOnMas
(const SortedTabOnMas<Tkey, Tval>& tab): _data(tab._data) {}

template<class Tkey, class Tval>
Tkey SortedTabOnMas<Tkey, Tval>::insert(Tval val) {
    Tkey key = generate_key<Tkey>();
    size_t pos = binary_search(key);
    _data.insert(TPair<Tkey, Tval>(key, val), pos);
    return key;
}

template<class Tkey, class Tval>
void SortedTabOnMas<Tkey, Tval>::insert(Tkey key, Tval val) {
    size_t pos = binary_search(key);
    if (_data[pos].first() != key) {
        TPair<Tkey, Tval> new_row(key, val);
        _data.insert(TPair<Tkey, Tval>(key, val), pos + 1);
    }
}

template<class Tkey, class Tval>
void SortedTabOnMas<Tkey, Tval>::erase(Tkey key) {
    size_t pos = binary_search(key);
    if (_data[pos].first() == key) {
        _data.remove_by_index(pos);
    } else {
        throw std::out_of_range("Key not found");
    }
}

template<class Tkey, class Tval>
Tval SortedTabOnMas<Tkey, Tval>::find(Tkey key) {
    size_t pos = binary_search(key);
    if(_data[pos].first() == key) return _data[pos].second();
    throw std::out_of_range("Key not found");
}

template<class Tkey, class Tval>
Tval SortedTabOnMas<Tkey, Tval>::operator[](Tkey key) {
    return find(key);
}

template<class Tkey, class Tval>
size_t SortedTabOnMas<Tkey, Tval>::binary_search(Tkey key) {
    size_t left = 0;
    size_t right = _data.size();

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if (_data[mid].first() < key) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    if (left < _data.size() && _data[left].first() == key) {
        return left;
    }
    return left - 1;
}

template<class Tkey, class Tval>
SortedTabOnMas<Tkey, Tval>& SortedTabOnMas<Tkey, Tval>::
operator=(const SortedTabOnMas<Tkey, Tval>& tab) {
    if (this != &tab) {
        _data = tab._data;
    }
    return *this;
}
