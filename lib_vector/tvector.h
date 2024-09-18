// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include "../lib_dmassive/archive.h"

template <typename T>
class TVector {
	TDMassive _data;
	size_t _start_index;

 public:
	 TVector();
	 TVector(const TVector& vec);
	 TVector(size_t start_index);
};
