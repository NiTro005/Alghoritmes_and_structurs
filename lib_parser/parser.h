// Copyright 2024 Kita Trofimov
#pragma once
#include "../lib_string/cstring.h"
#include "../lib_stack/stack.h"
#include "../lib_list/tlist.h"
#include "../lib_list/tnode.h"
#include "../lib_heap/heap.h"
#include "../lib_dsu/dsu.h"

bool IsCorrect(const CString& str);
template<typename T>
bool RabbitTurtleCycleList(const TList<T>& list);
template bool RabbitTurtleCycleList<int>(const TList<int>& list);

class Maze {
 private:
    int rows, cols;
    int** walls_h;
    int** walls_v;
    DSU dsu;

    int toIndex(int x, int y) const;
    void shuffle(int* array, int n);

 public:
    Maze(int r, int c);
    ~Maze();
    void generateMaze();
    void printMaze() const;
};

template<typename T>
void heapSort(T* array, size_t n, size_t k) {
    Heap<T> heap(k + 1, MIN);
    for (size_t i = 0; i <= k && i < n; ++i) {
        heap.insert(array[i]);
    }
    size_t j = 0;

    for (size_t i = k + 1; i < n; ++i) {
        array[j++] = heap.remove();
        heap.insert(array[i]);
    }

    while (!heap.is_empty()) {
        array[j++] = heap.remove();
    }
}

template<typename T>
void insertionSortK(T* array, size_t n, size_t k) {
    for (size_t i = 1; i < n; ++i) {
        T key = array[i];
        size_t j = i;

        size_t start = (i > k) ? i - k : 0;
        while (j > start && array[j - 1] > key) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = key;
    }
}

template <class T>
void link_lists(TList<T>& first, TList<T>& sec) {  // NOLINT(runtime/references)
    auto s = sec.begin();
    auto f = first.begin();
    TNode<T>* cur = first.head;
    while (f != first.end() && s != sec.end()) {
        if (*f < *s) {
            cur = f.getNode();
            f++;
        } else {
            first.insert(cur, *s);
            s++;
        }
    }
    while (s != sec.end()) {
        first.push_back(*s);
        s++;
    }
}


template<typename T>
struct CicleErr {
    bool has_cicle;
    size_t index_err;

    CicleErr() = default;

    CicleErr<T>& operator=(const CicleErr<T>& other) {
        if (this != &other) {
            has_cicle = other.has_cicle;
            index_err = other.index_err;
        }
        return *this;
    }
};

template<typename T>
CicleErr<T> UpheavalPointerCycleList
(TList<T>& list);  // NOLINT(runtime/references)
template CicleErr<int> UpheavalPointerCycleList
<int>(TList<int>& list);  // NOLINT(runtime/references)
