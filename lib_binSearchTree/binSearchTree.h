// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <algorithm>
#include "../lib_binSearchTree/binNode.h"

template<class T>
class TBinSearchTree {
 public:
    TBinNode<T>* _head = nullptr;
    TBinSearchTree() = default;
    TBinSearchTree(const TBinSearchTree& other);

    ~TBinSearchTree();

    TBinNode<T>* search(T val) const noexcept;
    TBinNode<T>* insert(T val);
    void erase(T val);
    T min(TBinNode<T>*& node);  // NOLINT(runtime/references)
    void clear() noexcept;
    void clear(TBinNode<T>* node) noexcept;
    size_t size() const;
 private:
     TBinNode<T>* getParent(TBinNode<T>* node) const;
     size_t size(TBinNode<T>* node) const;
};

template<class T>
TBinSearchTree<T>::TBinSearchTree(const TBinSearchTree& other) {
    _head = copyTree(other._head);
}

template<class T>
TBinSearchTree<T>::~TBinSearchTree() {
    clear();
}

template<class T>
TBinNode<T>* TBinSearchTree<T>::search(T val) const noexcept {
    TBinNode<T>* cur = _head;
    TBinNode<T>* pred = nullptr;

    while (cur != nullptr) {
        if (cur->value == val) {
            return cur;
        }
        pred = cur;
        if (cur->value < val) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }
    return pred;
}

template<class T>
TBinNode<T>* TBinSearchTree<T>::insert(T val) {
    TBinNode<T>* new_node = new TBinNode<T>(val);
    if (_head == nullptr) {
        _head = new_node;
        return new_node;
    }

    TBinNode<T>* node = search(val);
    if (node->value == val) {
        delete new_node;
        throw std::logic_error("This value is busy");
    }
    if (node->value < val) {
        node->right = new_node;
    } else {
        node->left = new_node;
    }

    return new_node;
}

template<class T>
void TBinSearchTree<T>::erase(T val) {
    TBinNode<T>* node = search(val);
    if (node == nullptr || node->value != val) {
        throw std::logic_error("No value");
    }

    TBinNode<T>* parent = getParent(node);
    if (node->left != nullptr && node->right != nullptr) {
        T minValue = min(node->right);
        node->value = minValue;
        return;
    }
    TBinNode<T>* child = (node->left != nullptr) ? node->left : node->right;
    if (parent == nullptr) {
        _head = child;
    } else {
        if (parent->left == node) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    }

    delete node;
}

template<class T>
T TBinSearchTree<T>::min(TBinNode<T>*& node) {  // NOLINT(runtime/references)
    if (node == nullptr) {
        throw std::logic_error("Node is nullptr");
    }

    TBinNode<T>* cur = node;
    TBinNode<T>* parent = nullptr;

    while (cur->left != nullptr) {
        parent = cur;
        cur = cur->left;
    }
    T value = cur->value;
    if (parent == nullptr) {
        node = cur->right;
    } else {
        parent->left = cur->right;
    }

    delete cur;
    return value;
}

template<class T>
TBinNode<T>* copyTree(TBinNode<T>* node) {
    if (node == nullptr) {
        return nullptr;
    }
    TBinNode<T>* newNode = new TBinNode<T>(node->value);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

template<class T>
void TBinSearchTree<T>::clear() noexcept {
    if (_head != nullptr) {
        clear(_head);
        _head = nullptr;
    }
}

template<class T>
void TBinSearchTree<T>::clear(TBinNode<T>* node) noexcept {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template<class T>
TBinNode<T>* TBinSearchTree<T>::getParent(TBinNode<T>* node) const {
    if (node == nullptr || node == _head) {
        return nullptr;
    }

    TBinNode<T>* cur = _head;
    TBinNode<T>* parent = nullptr;

    while (cur != nullptr) {
        if (cur->left == node || cur->right == node) {
            return cur;
        }
        if (node->value < cur->value) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    return nullptr;
}

template<class T>
size_t TBinSearchTree<T>::size() const {
    return size(_head);
}

template<class T>
size_t TBinSearchTree<T>::size(TBinNode<T>* node) const {
    if (node == nullptr) {
        return 0;
    }
    return 1 + size(node->left) + size(node->right);
}
