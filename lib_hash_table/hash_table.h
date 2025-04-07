//// Copyright 2024 Kita Trofimov
//#pragma once
//#include <iostream>
//
//#include "../lib_list/tlist.h"
//#include "../lib_pair/pair.h"
//#include "../lib_hash_table/colission.h"
//
//template <class Tkey, class Tval>
//class HashTable {
//    IColission<Tkey, Tval>* _strategy = nullptr;
//
// public:
//     HashTable(typeColission type) {
//         switch (type) {
//         case OpenAddress:
//             _strategy = new OpenAddressColission<Tkey, Tval>();
//         case Chain:
//             _strategy = new ChainStrategyColission<Tkey, Tval>();
//             break;
//         }
//     }
//
//     ~HashTable() {
//         delete _strategy;
//     }
//
//     HashTable(const HashTable&) = delete;
//     HashTable& operator=(const HashTable&) = delete;
//
//     void insert(Tkey key, Tval val) { _strategy->insert(key, val); }
//     void erase(Tkey key) { _strategy->remove(key); }
//     Tval find(Tkey key) { return _strategy->find(key); }
//     Tval operator[](Tkey key) { return (*_strategy)[key]; }
//};
