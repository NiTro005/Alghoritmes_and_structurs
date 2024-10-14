// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <utility>
#include "../lib_vector/tvector.h"

template<typename T>
class TMatrix {
    TVector<TVector<T>> matrix;
};