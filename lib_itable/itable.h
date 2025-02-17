// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
template<class Tkey, class Tval>
class ITable {
 public:
    virtual Tkey insert(TVal val);
    virtual void insert(Tkey key, Tval val);
    virtual void erase(TKey key);
    virtual Tval find(Tkey key);
    virtual Tval& operator[](Tkey key);
};
