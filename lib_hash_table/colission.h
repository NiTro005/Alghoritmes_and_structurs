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
     Tval operator[](Tkey key) override;
     ~OpenAddressColission() override = default;
     bool isFull() const noexcept;
     bool isEmpty() const noexcept;

 private:
     size_t search(Tkey key) override;
     size_t probe(size_t hash, size_t shift = 31) const;
     size_t findHash(Tkey key);
};

template <class Tkey, class Tval>
class ChainStrategyColission : public IColission<Tkey, Tval> {
    struct Node {
        TPair<Tkey, Tval> data;
        Node* next = nullptr;
        explicit Node(const TPair<Tkey, Tval>& data) : data(data) {}
        Node() = default;
    };
    Node* array[CAPACITY];

 public:
     ChainStrategyColission() = default;

     void insert(Tkey key, Tval val) override;
     void remove(Tkey key) override;
     Tval find(Tkey key) override;

     Tval operator[](Tkey key) override;
     ~ChainStrategyColission() override;
 private:
     size_t search(Tkey key) override;
};

template <class Tkey, class Tval>
size_t IColission<Tkey, Tval>::hashCode(Tkey key) {
    if constexpr (sizeof(Tkey) <= sizeof(size_t)) {
        return static_cast<size_t>(key) % CAPACITY;
    } else if constexpr (std::is_same_v<Tkey, std::string>) {
        const std::string& s = key;
        size_t sum = 0;
        for (char c : s) {
            sum += static_cast<unsigned char>(c);
        }
        return sum % CAPACITY;
    } else {
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
size_t OpenAddressColission<Tkey, Tval>::probe
(size_t hash, size_t shift) const {
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
void ChainStrategyColission<Tkey, Tval>::insert(Tkey key, Tval val) {
    size_t hash = search(key);
    Node* current = array[hash];

    while (current != nullptr) {
        if (current->data.first() == key) {
            current->data.set_second(val);
            return;
        }
        current = current->next;
    }

    Node* newNode = new Node(TPair<Tkey, Tval>(key, val));
    newNode->next = array[hash];
    array[hash] = newNode;
}

template<class Tkey, class Tval>
void ChainStrategyColission<Tkey, Tval>::remove(Tkey key) {
    size_t hash = search(key);
    Node* current = array[hash];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->data.first() == key) {
            if (prev == nullptr) {
                array[hash] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }

    throw std::logic_error("Key not found");
}

template<class Tkey, class Tval>
Tval ChainStrategyColission<Tkey, Tval>::find(Tkey key) {
    size_t hash = search(key);
    Node* current = array[hash];

    while (current != nullptr) {
        if (current->data.first() == key) {
            return current->data.second();
        }
        current = current->next;
    }

    throw std::logic_error("Key not found");
}

template<class Tkey, class Tval>
inline size_t ChainStrategyColission<Tkey, Tval>::search(Tkey key) {
    return hashCode(key);
}

template<class Tkey, class Tval>
inline Tval ChainStrategyColission<Tkey, Tval>::operator[](Tkey key) {
    return find(key);
}

template<class Tkey, class Tval>
ChainStrategyColission<Tkey, Tval>::~ChainStrategyColission() {
    for (size_t i = 0; i < CAPACITY; ++i) {
        Node* current = array[i];
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        array[i] = nullptr;
    }
}
