// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
template<class Tkey, class Tval>
class ITable {
 public:
    virtual Tkey insert(Tval val) = 0;
    virtual void insert(Tkey key, Tval val) = 0;
    virtual void erase(Tkey key) = 0;
    virtual Tval find(Tkey key) = 0;
    virtual Tval operator[](Tkey key) = 0;
};
