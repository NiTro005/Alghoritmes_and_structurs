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

template<class Tkey, class Tval>
TBSTable<Tkey, Tval>::TBSTable
(const TBSTable<Tkey, Tval>& tab) : _data(tab._data),
_size(tab._size) {}

template<class Tkey, class Tval>
Tkey TBSTable<Tkey, Tval>::insert(Tval val) {
    _size++;
    Tkey new_key = generate_key<Tkey>();
    TPair<Tkey, Tval> new_row(new_key, val);
    _data.insert(new_row);
    return new_key;
}

template<class Tkey, class Tval>
void TBSTable<Tkey, Tval>::insert(Tkey key, Tval val) {
    if (find(key) != Tval()) {
        throw std::logic_error("Key already exists");
    }
    _size++;
    TPair<Tkey, Tval> new_row(key, val);
    _data.insert(new_row);
}

template<class Tkey, class Tval>
void TBSTable<Tkey, Tval>::erase(Tkey key) {
    TPair<Tkey, Tval> pair_to_remove(key, Tval());
    if (_data.search(pair_to_remove)->value.first() != key) {
        throw std::out_of_range("Key not found");
    }
    _data.erase(pair_to_remove);
    _size--;
}

template<class Tkey, class Tval>
TBSTable<Tkey, Tval>::TBSTable
(const TBinSearchTree<TPair<Tkey, Tval>>& data) :
    _data(data), _size(data.size()) {}

template <class Tkey, class Tval>
Tval TBSTable<Tkey, Tval>::find(Tkey key) {
    if (_data._head != nullptr) {
        TPair<Tkey, Tval> pair_to_find(key, Tval());
        TBinNode<TPair<Tkey, Tval>>* result = _data.search(pair_to_find);
        if (result->value.first() == key) {
            return result->value.second();
        }
    }
    return Tval();
}

template<class Tkey, class Tval>
Tval TBSTable<Tkey, Tval>::operator[](Tkey key) {
    Tval val = find(key);
    return val;
}
