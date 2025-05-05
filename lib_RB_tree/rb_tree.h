// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <algorithm>
#include "../lib_RB_tree/rb_tree.h"

template <class T>
class RBTree {
    enum Color { RED, BLACK };
    struct RBNode {
        T _val;
        RBNode* _left;
        RBNode* _right;
        RBNode* _parent;
        Color _color;

        RBNode(const T& val)
            : _val(val), _left(nullptr), _right(nullptr),
            _parent(nullptr), _color(RED) {}

        RBNode(const RBNode& node)
            : _val(node._val), _left(nullptr), _right(nullptr),
            _parent(nullptr), _color(node._color) {}
    };

    RBNode* root = nullptr;

 public:
    RBTree() = default;
    RBTree(const RBTree& other);
    RBTree& operator=(const RBTree& other);
    ~RBTree();

    void insert(const T& val);
    void remove(const T& val);
    bool contains(const T& val) const;
    void printInOrder() const;
    bool isEmpty() const { return root == nullptr; }

 private:
    void leftRotate(RBNode* x);
    void rightRotate(RBNode* y);
    void fixInsert(RBNode* z);
    void fixDelete(RBNode* x);
    void transplant(RBNode* u, RBNode* v);
    RBNode* minimum(RBNode* node) const;
    RBNode* maximum(RBNode* node) const;
    RBNode* search(RBNode* node, const T& val) const;
    void printInOrder(RBNode* node) const;
    void deleteTree(RBNode* node);
    RBNode* copyTree(RBNode* node, RBNode* parent);
};

template <typename T>
RBTree<T>::RBTree(const RBTree& other) : root(nullptr) {
    if (!other.isEmpty()) {
        root = copyTree(other.root, nullptr);
    }
}

template <typename T>
RBTree<T>& RBTree<T>::operator=(const RBTree& other) {
    if (this != &other) {
        deleteTree(root);
        root = nullptr;
        if (!other.isEmpty()) {
            root = copyTree(other.root, nullptr);
        }
    }
    return *this;
}

template <typename T>
typename RBTree<T>::RBNode* RBTree<T>::copyTree(RBNode* node, RBNode* parent) {
    if (node == nullptr) {
        return nullptr;
    }

    RBNode* newNode = new RBNode(node->_val);
    newNode->_color = node->_color;
    newNode->_parent = parent;

    newNode->_left = copyTree(node->_left, newNode);
    newNode->_right = copyTree(node->_right, newNode);

    return newNode;
}

template <typename T>
RBTree<T>::~RBTree() {
    deleteTree(root);
}

template <typename T>
void RBTree<T>::deleteTree(RBNode* node) {
    if (node == nullptr) return;
    deleteTree(node->_left);
    deleteTree(node->_right);
    delete node;
}

template <typename T>
bool RBTree<T>::contains(const T& val) const {
    return search(root, val) != nullptr;
}

template <typename T>
typename RBTree<T>::RBNode*
RBTree<T>::search(RBNode* node, const T& val) const {
    while (node != nullptr && node->_val != val) {
        if (val < node->_val) {
            node = node->_left;
        } else {
            node = node->_right;
        }
    }
    return node;
}
