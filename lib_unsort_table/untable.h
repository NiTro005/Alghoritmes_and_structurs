// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <unordered_set>
#include <random>
#include <limits>

#include "../lib_list/tlist.h"
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
class UnsortedTable : public ITable<Tkey, Tval> {
    TList <TPair<Tkey, Tval>> _data;
    size_t _size = 0;

 public:
     UnsortedTable() = default;
     explicit UnsortedTable(const TList<TPair<Tkey, Tval>>& data);
     UnsortedTable(const UnsortedTable<Tkey, Tval>& tab);
     ~UnsortedTable() = default;
     Tkey insert(Tval val) override;
     void insert(Tkey key, Tval val) override;
     void erase(Tkey key) override;
     Tval find(Tkey key) override;
     Tval operator[](Tkey key) override;
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
    _size++;
    Tkey new_key = generate_key<Tkey>();
    TPair<Tkey, Tval> new_row(new_key, val);
    _data.push_back(new_row);
    return new_key;
}

template<class Tkey, class Tval>
void UnsortedTable<Tkey, Tval>::insert(Tkey key, Tval val) {
    try {
        find(key);
        throw std::logic_error("Key already exists");
    }
    catch (const std::out_of_range&) {
        _size++;
        TPair<Tkey, Tval> new_row(key, val);
        _data.push_back(new_row);
    }
}

template<class Tkey, class Tval>
void UnsortedTable<Tkey, Tval>::erase(Tkey key) {
    auto prev = _data.begin();
    for (auto it = _data.begin();
        it != _data.end(); ++it) {
        if ((*it).first() == key) {
            _data.erase(prev.getNode());
            _size--;
            return;
        }
        prev = it;
    }
    throw std::out_of_range("Key not found");
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
Tval UnsortedTable<Tkey, Tval>::operator[](Tkey key) {
    Tval val = find(key);
    return val;
}

template<class Tkey, class Tval>
UnsortedTable<Tkey, Tval>& UnsortedTable
<Tkey, Tval>::operator=(const UnsortedTable<Tkey,
    Tval>& tab) noexcept {
    if (this != &tab) {
        _data = tab._data;
        _size = tab._size;
    }
    return *this;
}
