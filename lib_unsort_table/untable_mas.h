// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_dmassive/archive.h"
#include "../lib_pair/pair.h"
#include "../lib_itable/itable.h"

template<class Tkey, class Tval>
class UnsortedTableMas : ITable<Tkey, Tval> {
    TDMassive<TPair<Tkey, Tval>> _data;

 public:
     UnsortedTableMas() = default;
     explicit UnsortedTableMas(const TDMassive<TPair<Tkey, Tval>>& data)
         : _data(data) {}
     UnsortedTableMas(const UnsortedTableMas<Tkey, Tval>& table) :
         _data(table._data) {}
     ~UnsortedTableMas() = default;

     Tkey insert(Tval val) override;
     void insert(Tkey key, Tval val) override;
     void erase(Tkey key) override;
     Tval find(Tkey key) override;
     Tval operator[](Tkey key) override;
     UnsortedTableMas& operator=
         (const UnsortedTableMas<Tkey, Tval>& tab) noexcept;
};

template<class Tkey, class Tval>
Tkey UnsortedTableMas<Tkey, Tval>::insert(Tval val) {
    Tkey new_key = generate_key<Tkey>();
    TPair<Tkey, Tval> new_row(new_key, val);
    _data.push_back(new_row);
    return new_key;
}

template<class Tkey, class Tval>
void UnsortedTableMas<Tkey, Tval>::insert(Tkey key, Tval val) {
    if (find(key) != Tval()) {
        throw std::logic_error("Key already exists");
    }
    TPair<Tkey, Tval> new_row(key, val);
    _data.push_back(new_row);
}

template<class Tkey, class Tval>
void UnsortedTableMas<Tkey, Tval>::erase(Tkey key) {
    size_t pos = 0;
    for (auto mas : _data) {
        if (mas.first() == key) {
            _data.remove_by_index(pos);
            return;
        }
        pos++;
    }
    throw std::out_of_range("Key not found");
}

template <class Tkey, class Tval>
Tval UnsortedTableMas<Tkey, Tval>::find(Tkey key) {
    for (auto mas : _data) {
        if (mas.first() == key) {
            return mas.second();
        }
    }
    return Tval();
}

template<class Tkey, class Tval>
Tval UnsortedTableMas<Tkey, Tval>::operator[](Tkey key) {
    Tval val = find(key);
    return val;
}

template<class Tkey, class Tval>
UnsortedTableMas<Tkey, Tval>& UnsortedTableMas
<Tkey, Tval>::operator=(const UnsortedTableMas<Tkey, Tval>& tab) noexcept {
    if (this != &tab) {
        _data = tab._data;
    }
    return *this;
}
