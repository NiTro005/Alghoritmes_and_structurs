// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <utility>
#include "../lib_list/tnode.h"

template <typename T> class TList;
template <typename T>
void asort(TList<T>& list) noexcept;  // NOLINT(runtime/references)
template <typename T>
class TList {
    template <class T>
    class TIterator;
 public:
     TNode<T>* head = nullptr;
     TNode<T>* last = nullptr;
     typedef TIterator<T> iterator;

     TList() = default;
     TList(const TList& list);
     ~TList();
     iterator begin() {
         return iterator(head);
     }

     iterator end() {
         return iterator(last->next());
     }

     void push_front(const T& value) noexcept;
     void push_back(const T& value) noexcept;
     void insert(TNode<T>* node, const T& value);
     void insert(size_t pos, const T& value);

     TNode<T>* find(const T& value) const noexcept;
     bool isEmpty() const noexcept;
     size_t size() const noexcept;
     void pop_front();
     void pop_back();
     void erase(TNode<T>* node);
     void erase(size_t pos);

     void replace(TNode<T>* node, const T& value);
     void replace(size_t pos, const T& value);

     friend void asort<T>
         (TList<T>& list) noexcept;  // NOLINT(runtime/references)

 private:
     template <class T>
     class TIterator {
         TNode<T>* pCur;
          
      public:
          TIterator() = default;
          TIterator(TNode<T>* nod) : pCur(nod) {}
          TIterator(const TIterator<T>& iter) : pCur(iter.pCur) {}
          TIterator<T>& operator++() {
              pCur = pCur->next();
              return *this;
          }

          TIterator<T> operator++(int) {
              TIterator<T> temp = *this;
              pCur = pCur->next();
              return temp;
          }
          bool operator!=(const TIterator<T>& other) const {
              return pCur != other.pCur;
          }

          bool operator==(const TIterator<T>& other) const {
              return pCur == other.pCur;
          }
          T operator*() { return pCur->value(); }

          const T& operator*() const {
              return pCur->value();
          }

     };
};


template<typename T>
TList<T>::TList<T>(const TList<T>& list) : head(list.head), last(list.last) {}

template<typename T>
TList<T>::~TList() {
    while (head != nullptr) {
        TNode<T>* link = head;
        head = head->next();
        delete link;
    }
}

template<typename T>
void TList<T>::push_front(const T& value) noexcept {
    if (head == nullptr) {
        head = new TNode<T>(value);
        last = head;
    } else {
        TNode<T>* link = new TNode<T>(value, head);
        head = link;
    }
}

template<typename T>
void TList<T>::push_back(const T& value) noexcept {
    TNode<T>* link = new TNode<T>(value);
    if (last == nullptr) {
        head = link;
        last = head;
    } else if (last == head) {
        head->next(link);
        last = link;
    } else {
        last->next(link);
        last = link;
    }
}

template<typename T>
void TList<T>::insert(TNode<T>* node, const T& value) {
    if (node == nullptr) {
        throw std::invalid_argument("Node pointer is nullptr");
    }
    if (node->next() == nullptr) {
        push_back(value);
    } else {
        TNode<T>* newNode = new TNode<T>(value, node->next());
        node->next(newNode);
    }
}

template<typename T>
void TList<T>::insert(size_t pos, const T& value) {
    TNode<T>* cur = head;
    if (pos == 0) {
        push_front(value);
        return;
    }
    for (size_t i = 0; i != pos; i++) {
        cur = cur->next();
        if (cur == nullptr) throw std::logic_error("Out of range");
    }
    insert(cur, value);
}

template<typename T>
TNode<T>* TList<T>::find(const T& value) const noexcept {
    if (!isEmpty()) {
        TNode<T>* cur(head);
        do {
            if (cur->value() == value) {
                return cur;
            }
            cur = cur->next();
        } while (cur != last);
    }
    return nullptr;
}

template<typename T>
inline bool TList<T>::isEmpty() const noexcept { return head == nullptr; }

template<typename T>
inline size_t TList<T>::size() const noexcept {
    size_t count = 0;
    TNode<T>* current = head;
    while (current->next() != last) {
        count++;
    }
    return count;
}

template<typename T>
void TList<T>::pop_front() {
    if (head == nullptr) throw std::runtime_error("List is empty");
    TNode<T>* temp = head;
    head = head->next();
    delete temp;
}

template<typename T>
void TList<T>::pop_back() {
    if (isEmpty()) throw std::runtime_error("List is empty");
    if (head == last) {
        delete head;
        head = nullptr;
        last = nullptr;
        return;
    }
    TNode<T>* current = head;
    while (current->next() != last) {
        current = current->next();
    }
    delete last;
    last = current;
    last->next(nullptr);
}

template<typename T>
void TList<T>::erase(TNode<T>* node) {
    if (node == nullptr) {
        throw std::invalid_argument("Node pointer is nullptr");
    }
    if (node == head) {
        pop_front();
        return;
    }
    if (node == last) {
        pop_back();
        return;
    }
    TNode<T>* link = node->next();
    node->next(node->next()->next());
    delete link;
}

template<typename T>
void TList<T>::erase(size_t pos) {
    TNode<T>* cur = head;
    if (pos == 0) {
        pop_front();
        return;
    }
    for (size_t i = 0; i != pos; i++) {
        cur = cur->next();
        if (cur == nullptr) {
            throw std::logic_error("Out of range");
        }
    }
    if (cur->next() == nullptr) {
        pop_back();
        return;
    }
    erase(cur);
}

template<typename T>
void TList<T>::replace(TNode<T>* node, const T& value) {
    if (node == nullptr) throw std::logic_error("link is null");
    node->set_value(value);
}

template<typename T>
void TList<T>::replace(size_t pos, const T& value) {
    TNode<T>* cur = head;
    for (size_t i = 0; i != pos; i++) {
        cur = cur->next();
        if (cur == nullptr) throw std::logic_error("Out of range");
    }
    replace(cur, value);
}

template<typename T>
void asort<T>(TList<T>& list) noexcept {  // NOLINT(runtime/references)
    if (list.head == nullptr || list.head->next() == nullptr) {
        return;
    }

    TNode<T>* sorted = nullptr;
    TNode<T>* current = list.head;
    while (current != nullptr) {
        TNode<T>* next = current->next();
        if (sorted == nullptr ||
            sorted->value() >= current->value()) {
            current->next(sorted);
            sorted = current;
        } else {
            TNode<T>* search = sorted;
            while (search->next() != nullptr &&
                search->next()->value() < current->value()) {
                search = search->next();
            }
            current->next(search->next());
            search->next(current);
        }
        current = next;
    }

    list.head = sorted;

    TNode<T>* temp = list.head;
    while (temp != nullptr && temp->next() != nullptr) {
        temp = temp->next();
    }
    list.last = temp;
}
