// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_list/tlist.h"
#include "../lib_pair/pair.h"
#include "../lib_itable/itable.h"

template <class Tkey, class Tval>
class UnsortedTable : ITable<Tkey, Tval> {
    TList <TPair<Tkey, Tval>> _data;
    size_t _size;

 public:
     UnsortedTable();
     UnsortedTable(const TList<Pair<Tkey, Tval>>& data);
     UnsortedTable(const UnsortedTable<Pair<Tkey, Tval>>& tab);
     
     Tkey insert(Tval val) override noexcept;
     void insert(Tkey key, Tval val) override;
     void erase(TKey key, Tval val) override;
     Tval find(Tkey key) override const noexcept;

     Tval& operator[](Tkey key) override const;
     UnsortedTable& operator=(const UnsortedTable<Tkey, Tval>& tab) noexcept;
};
