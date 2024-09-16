// Copyright 2024 Kita Trofimov

#include <iostream>
#include "../lib_dmassive/archive.h"

template <typename T>
class TStack {
	TDMassive<T> _data;
 public:
	 TStack(size_t size = 20);
	 ~TStack();

	 inline size_t size() const noexcept;

	 inline bool IsEmpty() const noexcept;
	 inline bool IsFull() const noexcept;

	 void push(T value);
	 void pop();
	 inline T top() const;
};

template <typename T>
TStack<T>::TStack(size_t size) : _data(size) {}

template <typename T>
inline size_t TStack<T>::size() const noexcept {
	return _data.capacity();
}

template <typename T>
TStack<T>::~TStack(){}

template <typename T>
inline bool TStack<T>:: IsEmpty() const noexcept {
	return _data.empty();
}

template <typename T>
inline bool TStack<T>:: IsFull() const noexcept {
	return _data.full();
}

template<typename T>
void TStack<T>:: push(T value){
	if (!IsFull()) {
		_data.push_front(value);
	} else {
		throw std::out_of_range("Error:Overlow stack");
	}
}

template<typename T>
inline void TStack<T>::pop(){
	if (!IsEmpty()) {
		_data.pop_front();
	}
	else {
		throw std::out_of_range("Stack is empty");
	}
}

template<typename T>
inline T TStack<T>::top() const
{
	if (IsEmpty()) {
		throw std::out_of_range("Stack is empty");
	}
	return _data.data()[0];
}
