// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>

#include "../lib_list/tlist.h"
#include "../lib_pair/pair.h"

enum typeColission {
    OpenAddress, Chain
};

template <class Tkey, class Tval>
class IColission {
 public:
     virtual void insert(Tkey key, Tval val) = 0;
     virtual void erase(Tkey key) = 0;
     virtual Tval find(Tkey key) = 0;
     virtual size_t search(Tkey key) = 0;
     virtual Tval operator[](Tkey key) = 0;
};

template <class Tkey, class Tval>
class OpenAddressColission : public IColission<Tkey, Tval>{

};

template <class Tkey, class Tval>
class ChainStrategyColission : public IColission<Tkey, Tval> {

};
