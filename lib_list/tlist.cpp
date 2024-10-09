// Copyright 2024 Kita Trofimov
#include "../lib_list/tlist.h"

template<typename T>
void asort(TList<T>& list) noexcept {
    if (list.head == nullptr || list.head->next() == nullptr) {
        return;
    }

    TNode<T>* sorted = nullptr;
    TNode<T>* current = list.head;
    while (current != nullptr) {
        TNode<T>* next = current->next();
        if (sorted == nullptr || sorted->value() >= current->value()) {
            current->next(sorted);
            sorted = current;
        } else {
            TNode<T>* search = sorted;
            while (search->next() != nullptr && search->next()->value() < current->value()) {
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
