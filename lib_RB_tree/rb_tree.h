// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <algorithm>
#include "../lib_RB_tree/rb_tree.h"

class RBTree {
    struct RBNode {
        RBNode* _left, * _right, * _parent;
        bool _color;
        RBNode() : _left(nullptr), _right(nullptr),
            _parent(nullptr), _color(true) {}
        RBNode(const RBNode& node) :_left(node._left), _right(node._right),
            _parent(node._parent), _color(node._color) {}
    };
    RBNode* head = nullptr;

 public:
    RBTree() = default;
    ~RBTree();

    void insert(int key);
    void remove(int key);
    bool contains(int key);
    void printInOrder();
    bool isEmpty() const { return head == nullptr; }

 private:
    void printInOrder(RBNode* node);

    void leftRotate(RBNode* x);
    void rightRotate(RBNode* y);
    void fixInsert(RBNode* node);
    void fixDelete(RBNode* node);
    void transplant(RBNode* u, RBNode* v);
    RBNode* minimum(RBNode* node);
    RBNode* search(RBNode* node, int key);
    void deleteTree(RBNode* node);
};
