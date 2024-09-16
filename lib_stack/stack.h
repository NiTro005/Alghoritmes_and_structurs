// Copyright 2024 Kita Trofimov

#include <iostream>
#include "../lib_dmassive/archive.h"

template <typename T>
class TStack {
	TDMassive<T> _data;
 public:
	 TStack(size_t size = 20);
	// ~TStack();

	 size_t size();

	// inline bool IsEmpty() const noexcept;
	 //inline bool IsFool() const noexcept;

	/// void push();
	 ///void pop();
	 ///inline T top() const noexcept;
};

template <typename T>
TStack<T>::TStack(size_t size) : _data(size) {}

template <typename T>
size_t TStack<T>::size() {
	return _data.capacity();
}

//template <typename T>
//TStack<T>::~TStack(){}
//
//inline bool IsEmpty() const noexcept {
//	return _data->empty();
//}
//
//inline bool IsFull() const noexcept {
//	return _data->full();
//}