// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <algorithm>
#include "../lib_RB_tree/rb_tree.h"


template <class T>
class RBTree {
    struct RBNode {
     public:
        T _val;
        RBNode* _left;
        RBNode* _right;
        RBNode* _parent;
        bool _color;

        explicit RBNode(const T& val)
            : _val(val), _left(nullptr), _right(nullptr),
            _parent(nullptr), _color(true) {}

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
    bool validate() const;

 private:
    void leftRotate(RBNode* x);
    void rightRotate(RBNode* y);
    void fixInsert(RBNode* z);
    void fixDelete(RBNode* x);
    void transplant(RBNode* u, RBNode* v);
    RBNode* minimum(RBNode* node) const;
    RBNode* maximum(RBNode* node) const;
    RBNode* search(const T& val) const;
    void print(RBNode* node, int indent = 0) const;
    void deleteTree(RBNode* node);
    RBNode* copyTree(RBNode* node, RBNode* parent);
    bool checkRedBlackProperties
    (RBNode* node, int currentBlackHeight, int& expectedBlackHeight) const;
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
typename RBTree<T>::RBNode* RBTree<T>::copyTree
(RBNode* node, RBNode* parent) {
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

template<class T>
void RBTree<T>::insert(const T& val) {
    RBNode* leaf = new RBNode(val);
    if (isEmpty()) {
        leaf->_color = false;
        root = leaf;
        return;
    }

    RBNode* parent = search(val);
    if (parent->_val == val) {
        delete leaf;
        throw std::logic_error("This value already exists");
    }

    leaf->_parent = parent;
    if (val < parent->_val) {
        parent->_left = leaf;
    } else {
        parent->_right = leaf;
    }

    if (parent->_color == false) {
        return;
    }

    fixInsert(leaf);
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
    return search(val) != nullptr;
}

template<class T>
inline void RBTree<T>::printInOrder() const {
    print(root);
}

template <typename T>
typename RBTree<T>::RBNode*
RBTree<T>::search(const T& val) const {
    RBNode* current = root;
    RBNode* parent = nullptr;

    while (current != nullptr) {
        if (current->_val == val) {
            return current;
        }
        parent = current;
        if (val < current->_val) {
            current = current->_left;
        }
        else {
            current = current->_right;
        }
    }

    return parent;
}

template<class T>
void RBTree<T>::fixInsert(RBNode* z) {
    while (z != root && z->_parent->_color == true) {
        RBNode* grandparent = z->_parent->_parent;
        if (z->_parent == grandparent->_left) {
            RBNode* uncle = grandparent->_right;

            if (uncle != nullptr && uncle->_color == true) {
                z->_parent->_color = false;
                uncle->_color = false;
                grandparent->_color = true;
                z = grandparent;
            } else {
                if (z == z->_parent->_right) {
                    z = z->_parent;
                    leftRotate(z);
                }
                z->_parent->_color = false;
                grandparent->_color = true;
                rightRotate(grandparent);
            }
        } else {
            RBNode* uncle = grandparent->_left;

            if (uncle != nullptr && uncle->_color == true) {
                z->_parent->_color = false;
                uncle->_color = false;
                grandparent->_color = true;
                z = grandparent;
            } else {
                if (z == z->_parent->_left) {
                    z = z->_parent;
                    rightRotate(z);
                }
                z->_parent->_color = false;
                grandparent->_color = true;
                leftRotate(grandparent);
            }
        }
    }
    root->_color = false;
}

template<class T>
void RBTree<T>::leftRotate(RBNode* x) {
    RBNode* y = x->_right;
    x->_right = y->_left;

    if (y->_left != nullptr) {
        y->_left->_parent = x;
    }

    y->_parent = x->_parent;

    if (x->_parent == nullptr) {
        root = y;
    } else if (x == x->_parent->_left) {
        x->_parent->_left = y;
    } else {
        x->_parent->_right = y;
    }

    y->_left = x;
    x->_parent = y;
}

template<class T>
void RBTree<T>::rightRotate(RBNode* y) {
    RBNode* x = y->_left;
    y->_left = x->_right;

    if (x->_right != nullptr) {
        x->_right->_parent = y;
    }

    x->_parent = y->_parent;

    if (y->_parent == nullptr) {
        root = x;
    } else if (y == y->_parent->_right) {
        y->_parent->_right = x;
    } else {
        y->_parent->_left = x;
    }

    x->_right = y;
    y->_parent = x;
}

template<class T>
void RBTree<T>::print(RBNode* node, int indent) const {
    if (node == nullptr) {
        return;
    }
    print(node->_right, indent + 4);

    for (int i = 0; i < indent; ++i) {
        std::cout << ' ';
    }
    if (node->_color == true) {
        std::cout << "\033[1;31m";
        std::cout << node->_val;
        std::cout << "\033[0m";
    }
    else {
        std::cout << node->_val;
    }
    print(node->_left, indent + 4);
}

template <typename T>
bool RBTree<T>::validate() const {
    if (root == nullptr) {
        return true;
    }

    if (root->_color != false) {
        std::cerr << "Violation: Root is not black" << std::endl;
        return false;
    }

    int blackHeight = -1;
    return checkRedBlackProperties(root, 0, blackHeight);
}

template <typename T>
bool RBTree<T>::checkRedBlackProperties
(RBNode* node, int currentBlackHeight, int& expectedBlackHeight) const {
    if (node == nullptr) {
        if (expectedBlackHeight == -1) {
            expectedBlackHeight = currentBlackHeight;
            return true;
        } else {
            return currentBlackHeight == expectedBlackHeight;
        }
    }

    if (node->_color == true) {
        if ((node->_left != nullptr && node->_left->_color == true) ||
            (node->_right != nullptr && node->_right->_color == true)) {
            std::cerr << "Violation: Red node has red child" << std::endl;
            return false;
        }
    }

    int newBlackHeight = currentBlackHeight + (node->_color == false ? 1 : 0);

    bool leftValid = checkRedBlackProperties
    (node->_left, newBlackHeight, expectedBlackHeight);
    bool rightValid = checkRedBlackProperties
    (node->_right, newBlackHeight, expectedBlackHeight);

    return leftValid && rightValid;
}
