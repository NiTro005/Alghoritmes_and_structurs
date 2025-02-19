// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_list/tlist.h"
#include "../lib_pair/pair.h"
#include "../lib_itable/itable.h"

template <class Tkey, class Tval>
class UnsortedTable : public ITable<Tkey, Tval> {
    TList <TPair<Tkey, Tval>> _data;
    size_t _size = 0;

 public:
     UnsortedTable() = default;
     UnsortedTable(const TList<TPair<Tkey, Tval>>& data);
     UnsortedTable(const UnsortedTable<Tkey, Tval>& tab);
     ~UnsortedTable() = default;
     
     Tkey insert(Tval val) override;
     void insert(Tkey key, Tval val) override;
     void erase(Tkey key) override;
     Tval find(Tkey key) override;

     Tval& operator[](Tkey key) override;
     UnsortedTable& operator=(const UnsortedTable<Tkey, Tval>& tab) noexcept;
};

template<class Tkey, class Tval>
inline UnsortedTable<Tkey, Tval>::UnsortedTable
(const TList<TPair<Tkey, Tval>>& data):
    _data(data), _size(data.size()) {}

template<class Tkey, class Tval>
inline UnsortedTable<Tkey, Tval>::UnsortedTable
(const UnsortedTable<Tkey, Tval>& tab): _data(tab._data),
_size(tab._size) {}

template<class Tkey, class Tval>
Tkey UnsortedTable<Tkey, Tval>::insert(Tval val) {
    return Tkey();
}

template<class Tkey, class Tval>
void UnsortedTable<Tkey, Tval>::insert(Tkey key, Tval val) {
    if (find(key) == NULL) {
        throw std::logic_error("No value");
    }
    _size++;
    TPair<Tkey, Tval> new_row(key, val);
    _data.push_back(new_row);
}

template<class Tkey, class Tval>
void UnsortedTable<Tkey, Tval>::erase(Tkey key) {

}

template <class Tkey, class Tval>
Tval UnsortedTable<Tkey, Tval>::find(Tkey key) {
    for (auto pair : _data) {
        if (pair.first() == key) {
            return pair.second();
        }
    }
    throw std::out_of_range("Key not found");
}

template<class Tkey, class Tval>
Tval& UnsortedTable<Tkey, Tval>::operator[](Tkey key) {
    Tval val = find(key);
    return val;
}
