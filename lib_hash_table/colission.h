// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <type_traits>
#include <string>
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
    int _size = 0;

 public:
     OpenAddressColission() = default;
     void insert(Tkey key, Tval val) override;
     void remove(Tkey key) override;
     Tval find(Tkey key) override;
     size_t search(Tkey key) override;
     Tval operator[](Tkey key) override;
     ~OpenAddressColission() override = default;
     bool isFull() const noexcept;
     bool isEmpty() const noexcept;

 private:
     size_t probe(size_t hash, size_t shift = 31) const;
     size_t findHash(Tkey key);
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
    if constexpr (sizeof(Tkey) <= sizeof(size_t)) {
        return static_cast<size_t>(key) % CAPACITY;
    }
    else if constexpr (std::is_same_v<Tkey, std::string>) {
        const std::string& s = key;
        size_t sum = 0;
        for (char c : s) {
            sum += static_cast<unsigned char>(c);
        }
        return sum % CAPACITY;
    }
    else {
        size_t sum = 0;
        const unsigned char* p = reinterpret_cast<const unsigned char*>(&key);
        for (size_t i = 0; i < sizeof(Tkey); i++) {
            sum += p[i];
        }
        return sum % CAPACITY;
    }
}

template<class Tkey, class Tval>
bool OpenAddressColission<Tkey, Tval>::isEmpty() const noexcept {
    return _size == 0;
}

template<class Tkey, class Tval>
void OpenAddressColission<Tkey, Tval>::insert(Tkey key, Tval val) {
    if (!isFull()) {
        size_t hash = search(key);
        if (hash != NULL) {
            array[hash].data = TPair<Tkey, Tval>(key, val);
            _size++;
        } else {
            throw std::logic_error("key is not exists");
        }
    } else {
        throw std::logic_error("array is full");
    }
}

template<class Tkey, class Tval>
void OpenAddressColission<Tkey, Tval>::remove(Tkey key) {
    if (!isEmpty()) {
        size_t hash = findHash(key);
        array[hash]._state = Node::deleted;
        _size--;
    } else {
        throw std::logic_error("array is empty");
    }
}

template<class Tkey, class Tval>
Tval OpenAddressColission<Tkey, Tval>::find(Tkey key) {
    size_t hash = findHash(key);
    if (hash == NULL) throw std::logic_error("no key");
    return array[hash].data.second();
}

template<class Tkey, class Tval>
size_t OpenAddressColission<Tkey, Tval>::search(Tkey key) {
    size_t hash = hashCode(key);
    while (array[hash]._state == Node::busy) {
        if (array[hash].data == key) return NULL;
        hash = probe(hash);
    }
    return hash;
}

template<class Tkey, class Tval>
inline Tval OpenAddressColission<Tkey, Tval>::operator[](Tkey key) {
    return find(key);
}

template<class Tkey, class Tval>
inline bool OpenAddressColission<Tkey, Tval>::isFull()
const noexcept {
    return _size == CAPACITY;
}

template<class Tkey, class Tval>
size_t OpenAddressColission<Tkey, Tval>::probe(size_t hash, size_t shift) const {
    return (hash + shift) & (CAPACITY - 1);
}

template<class Tkey, class Tval>
size_t OpenAddressColission<Tkey, Tval>::findHash(Tkey key) {
    size_t hash = hashCode(key);
    size_t start_hash = hash;
    do {
        if (array[hash].data == key) {
            if (array[hash]._state == Node::deleted) return NULL;
            return hash;
        }
        hash = probe(hash);
    } while (array[hash]._state != Node::empty || hash == start_hash);

    return NULL;
}

template<class Tkey, class Tval>
inline void ChainStrategyColission<Tkey, Tval>::insert(Tkey key, Tval val)
{
}

template<class Tkey, class Tval>
inline void ChainStrategyColission<Tkey, Tval>::remove(Tkey key)
{
}

template<class Tkey, class Tval>
inline Tval ChainStrategyColission<Tkey, Tval>::find(Tkey key)
{
    return Tval();
}

template<class Tkey, class Tval>
inline size_t ChainStrategyColission<Tkey, Tval>::search(Tkey key)
{
    return size_t();
}

template<class Tkey, class Tval>
inline Tval ChainStrategyColission<Tkey, Tval>::operator[](Tkey key)
{
    return Tval();
}

template<class Tkey, class Tval>
inline ChainStrategyColission<Tkey, Tval>::~ChainStrategyColission()
{
}
