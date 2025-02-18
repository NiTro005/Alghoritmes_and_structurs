// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_list/tlist.h"
#include "../lib_pair/pair.h"
#include "../lib_itable/itable.h"

template <class Tkey, class Tval>
class UnsortedTable : ITable<Tkey, Tval> {
    TList <TPair<Tkey, Tval>> _data;
    size_t _size = 0;

 public:
     UnsortedTable();
     UnsortedTable(const TList<TPair<Tkey, Tval>>& data);
     UnsortedTable(const UnsortedTable<Tkey, Tval>& tab);
     
     Tkey insert(Tval val) override noexcept;
     void insert(Tkey key, Tval val) override;
     /*void erase(Tkey key, Tval val) override;*/
     Tval find(Tkey key) override const noexcept;

     Tval& operator[](Tkey key) override const;
     /*UnsortedTable& operator=(const UnsortedTable<Tkey, Tval>& tab) noexcept;*/
};

template<class Tkey, class Tval>
inline UnsortedTable<Tkey, Tval>::UnsortedTable() {}

template<class Tkey, class Tval>
inline UnsortedTable<Tkey, Tval>::UnsortedTable
(const TList<TPair<Tkey, Tval>>& data):
    _data(data), _size(data.size()) {}

template<class Tkey, class Tval>
inline UnsortedTable<Tkey, Tval>::UnsortedTable
(const UnsortedTable<Tkey, Tval>& tab): _data(tab._data),
_size(tab._size) {}

template<class Tkey, class Tval>
void UnsortedTable<Tkey, Tval>::insert(Tkey key, Tval val) {
    if (find(key) == NULL) {
        std::logic_error("No value");
    }
    size++;
    TPair<Tkey, Tval> new_row(key, val);
    _data.push_back(new_row);
}

template <class Tkey, class Tval>
Tval UnsortedTable<Tkey, Tval>::find(Tkey key) {
    for (auto pair : _data) {
        if (pair.first() == key) {
            return pair.second();
        }
    }
    return null;
}
