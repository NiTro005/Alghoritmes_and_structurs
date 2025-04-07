// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>

#include "../lib_list/tlist.h"
#include "../lib_pair/pair.h"
#define CAPACITY 65536

enum typeColission {
    OpenAddress, Chain
};

template <class Tkey, class Tval>
class IColission {
 public:
     virtual void insert(Tkey key, Tval val) = 0;
     virtual void remove(Tkey key) = 0;
     virtual Tval find(Tkey key) = 0;
     virtual size_t search(Tkey key) = 0;
     virtual Tval operator[](Tkey key) = 0;
     virtual ~IColission() = default;
 protected:
     size_t hashCode(Tkey key);
};

template <class Tkey, class Tval>
class OpenAddressColission : public IColission<Tkey, Tval>{
    struct Node {
        enum state { deleted, busy, empty }; 
        state _state = empty;
        TPair<Tkey, Tval> data;
    };
    Node array[CAPACITY];

 public:
     OpenAddressColission() = default;
     void insert(Tkey key, Tval val) override;
     void remove(Tkey key) override;
     Tval find(Tkey key) override;
     size_t search(Tkey key) override;
     Tval operator[](Tkey key) override;
     ~OpenAddressColission() override = default;

 private:
     size_t probe(Tkey key, size_t attempt) const =
         (hash + attempt) & (CAPACITY - 1);
};

template <class Tkey, class Tval>
class ChainStrategyColission : public IColission<Tkey, Tval> {
    struct Node {
        TPair<Tkey, Tval> date;
        Node* next = nullptr;
    };
    Node* array[CAPACITY];

 public:
     ChainStrategyColission() = default;

     void insert(Tkey key, Tval val) override;
     void remove(Tkey key) override;
     Tval find(Tkey key) override;
     size_t search(Tkey key) override;
     Tval operator[](Tkey key) override;
     ~ChainStrategyColission() override;
};

template <class Tkey, class Tval>
size_t IColission<Tkey, Tval>::hashCode(Tkey key) {
    if (sizeof(Tkey) <= sizeof(size_t)) {
        return (size_t)key % CAPACITY;
    } else if (sizeof(Tkey) == sizeof(const char*)) {
        const char* str = (const char*)key;
        if (!str) return 0;
        size_t hash = 0;
        while (*str) hash = hash * 31 + *str++;
        return hash % CAPACITY;
    } else {
        size_t hash = 0;
        const unsigned char* p = (const unsigned char*)&key;
        for (size_t i = 0; i < sizeof(Tkey); i++) {
            hash = hash * 31 + p[i];
        }
        return hash % CAPACITY;
    }
}

template<class Tkey, class Tval>
size_t OpenAddressColission<Tkey, Tval>::search(Tkey key) {
    size_t hash = hashCode(key);
    for(size_t i = 0; data[i].date.first != key; i = probe(, 31))
    return size_t();
}
