// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <utility>
#define STEP_CAPACITY 15
#define MAX_CAPACITY 100000

enum State { empty, busy, deleted };

namespace algorithm {
    template<typename T>
    inline void swap(T& val_1, T& val_2) noexcept {
        T tmp = val_1;
        val_1 = val_2;
        val_2 = tmp;
    }
}

template <typename T>
class TDMassive {
    T* _data;
    State* _states;
    size_t _capacity;
    size_t _size;
    size_t _deleted;

 public:
    TDMassive();
    TDMassive(const TDMassive& archive);
    TDMassive(const T* arr, size_t n);
    TDMassive(size_t n, T value);
    TDMassive(const TDMassive& archive, size_t pos, size_t n);
    explicit TDMassive(size_t n);

    ~TDMassive();

    void print() const noexcept;

    inline bool empty() const noexcept;
    inline bool full() const noexcept;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    State get_state(size_t index) const;

    const T* data() const;

    void swap(TDMassive& archive);

    TDMassive& assign(const TDMassive& archive);

    void clear();
    void resize(size_t n, T value = NULL);
    void reserve(size_t n = 15);

    void push_back(T value);
    void pop_back();
    void push_front(T value);
    void pop_front();

    TDMassive& insert(const T* arr, size_t n, size_t pos);
    TDMassive& insert(T value, size_t pos);

    TDMassive& replace(size_t pos, T new_value);

    TDMassive& erase(size_t pos, size_t n);
    TDMassive& remove_all(T value);
    TDMassive& remove_first(T value);
    TDMassive& remove_last(T value);
    TDMassive& remove_by_index(size_t pos);

    size_t* find_all(T value) const noexcept;
    size_t find_first(T value) const;
    size_t find_last(T value) const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

 private:
    size_t count_value(T value)  const noexcept;
    void repacking();
};

template <typename T>
TDMassive<T>::TDMassive() {
    _size = 0;
    _capacity = STEP_CAPACITY;
    _data = new T[_capacity];
    _states = new State[_capacity];
    _deleted = 0;
    for (size_t i = 0; i < STEP_CAPACITY; i++) {
        _states[i] = State::empty;
    }
}

template <typename T>
TDMassive<T>::TDMassive(size_t n) {
    _capacity = n;
    _size = 0;
    _deleted = 0;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (size_t i = 0; i < _capacity; i++) {
        _states[i] = State::empty;
    }
}

template <typename T>
TDMassive<T>::TDMassive(const TDMassive& archive) {
    _capacity = archive._capacity;
    _size = archive._size;
    _deleted = archive._deleted;

    _data = new T[_capacity];
    _states = new State[_capacity];

    for (size_t i = 0; i < _size; i++) {
        _data[i] = archive._data[i];
        _states[i] = archive._states[i];
    }
}

template <typename T>
TDMassive<T>::TDMassive(const T* arr, size_t n) {
    _capacity = (n / STEP_CAPACITY)* STEP_CAPACITY + STEP_CAPACITY;
    _size = n;
    _deleted = 0;

    _data = new T[_capacity];
    _states = new State[_capacity];

    for (size_t i = 0; i < _size; i++) {
        _data[i] = arr[i];
        _states[i] = State::busy;
    }
}

template <typename T>
TDMassive<T>::TDMassive(size_t n, T value) {
    _capacity = (n / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _size = n;
    _deleted = 0;

    _data = new T[_capacity];
    _states = new State[_capacity];

    for (size_t i = 0; i < _size; i++) {
        _data[i] = value;
        _states[i] = State::busy;
    }
}

template <typename T>
TDMassive<T>::TDMassive(const TDMassive& archive, size_t pos, size_t n) {
    _capacity = (n / STEP_CAPACITY)* STEP_CAPACITY + STEP_CAPACITY;
    _size = n;
    _deleted = 0;

    _data = new T[_capacity];
    _states = new State[_capacity];

    for (size_t i = 0; i < n; i++) {
        if (pos + i < archive._size) {
            _data[i] = archive._data[pos + i];
            _states[i] = archive._states[pos + i];
        } else {
            _data[i] = T();
            _states[i] = State::empty;
        }
    }
}

template <typename T>
size_t TDMassive<T>::size() const noexcept {
    return _size;
}
template <typename T>
size_t TDMassive<T>::capacity() const noexcept {
    return _capacity;
}
template <typename T>
State TDMassive<T>::get_state(size_t index) const {
    return _states[index];
}

template <typename T>
const T* TDMassive<T> ::data() const {
    return _data;
}

template <typename T>
void TDMassive <T>::swap(TDMassive& archive) {
    algorithm::swap(_size, archive._size);
    algorithm::swap(_capacity, archive._capacity);
    algorithm::swap(_data, archive._data);
    algorithm::swap(_states, archive._states);
    algorithm::swap(_deleted, archive._deleted);
}

template <typename T>
TDMassive<T>& TDMassive <T>::assign(const TDMassive& archive) {
    delete[] _data;
    delete[] _states;
    _size = archive._size;
    _capacity = archive._capacity;
    _data = new T[_capacity];
    _states = new State[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = archive._data[i];
        _states[i] = archive._states[i];
    }
    return *this;
}

template <typename T>
void TDMassive<T>::clear() {
    delete[] _data;
    delete[] _states;
    _data = nullptr;
    _states = nullptr;
    _size = 0;
    _capacity = 0;
    _deleted = 0;
}

template <typename T>
void TDMassive <T>::resize(size_t n, T value) {
    if (n <= _size) {
        for (size_t i = _size; i >= n; i--) {
            _states[i] = State::empty;
        }
        _size = n;
    } else {
        if (n > _capacity) {
            reserve(n);
        }
        for (size_t i = _size; i < n; ++i) {
            _states[i] = State::busy;
            _data[i] = value;
        }
        _size = n;
    }
}

template <typename T>
void TDMassive <T>::reserve(size_t n) {
    repacking();
    if (n < _capacity ||(_size < _capacity && n <= _capacity)) {
        return;
    }
    _capacity = (n / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    if (_capacity > MAX_CAPACITY) {
        throw std::logic_error("Error in function" \
                               "void TArchive<T>::reserve(size_t n)\":"
                               " complete max size of capacity.");
    }
    T* newData = new T[_capacity];
    std::memcpy(newData, _data, _size);
    delete[] _data;
    _data = newData;
    State* newDat = new State[_capacity];
    std::memcpy(newDat, _states, _size);
    delete[] _states;
    _states = newDat;
}

template <typename T>
void TDMassive<T>::repacking() {
    int step = 0;
    int newSize = 0;
    for (int i = 0; i < _size; i++) {
        if (_states[i] == State::deleted) {
            step++;
        } else {
            _data[i - step] = _data[i];
            _states[i - step] = _states[i];
        }
    }
    newSize = _size - step;
    for (int i = newSize; i < _size; i++) {
        _states[i] = State::empty;
    }
    _size = newSize;
}

template <typename T>
TDMassive<T>::~TDMassive() {
    delete[] _data;
    _data = nullptr;
}

template <typename T>
inline bool TDMassive<T>::empty() const noexcept {
    return _size == 0;
}

template <typename T>
inline bool TDMassive<T>::full() const noexcept {
    return _size == _capacity;
}

template <typename T>
TDMassive<T>& TDMassive<T>::insert(T value, size_t pos) {
    if (_size < pos) {
        throw std::logic_error("Error in function" \
                               "TArchive<T>& insert(T value, size_t pos)\":"
                               " wrong position value.");
    }
    if (this->full()) {
        this->reserve();
    }
    for (size_t i = _size; i > pos; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[pos] = value;
    _states[pos] = State::busy;
    _size++;
    return *this;
}

template <typename T>
TDMassive<T>& TDMassive<T>::insert(const T* arr, size_t n, size_t pos) {
    if (_size < pos) {
        throw std::logic_error("Error in function" \
        "TArchive<T>& insert(T value, size_t pos)\":"
        " wrong position value.");
    }

    if ((_capacity - _size) < n) {
        reserve(_size + n);
    }
    for (size_t i = _size; i > pos; i--) {
        _data[i + n - 1] = _data[i - 1];
        _states[i + n - 1] = _states[i - 1];
    }
    for (size_t i = 0; i < n; ++i) {
        _data[pos + i] = arr[i];
        _states[pos + i] = State::busy;
    }
    _size += n;
    return *this;
}

template <typename T>
void TDMassive<T>::push_back(T value) {
    if (this->full()) {
        this->reserve();
    }
    _data[_size] = value;
    _states[_size] = State::busy;
    _size++;
}

template <typename T>
void TDMassive<T>::push_front(T value) {
    if (this->full()) {
        this->reserve();
    }
    for (size_t i = _size; i > 0; i--) {
        _data[i] = _data[i - 1];
        _states[i] = _states[i - 1];
    }
    _data[0] = value;
    _states[0] = State::busy;
    _size++;
}

template <typename T>
void TDMassive<T>::pop_front() {
    if (_size <= 0) {
        throw std::logic_error("Error in function" \
                               "void TArchive<T>::pop_front()\":"
                               "archive clear");
    }
    for (size_t i = 1; i < _size; i++) {
        _data[i - 1] = _data[i];
        _states[i - 1] = _states[i];
    }
    _states[_size - 1] = State::deleted;
    _deleted++;
    _size--;
}

template <typename T>
void TDMassive<T>::pop_back() {
    if (_size <= 0) {
        throw std::logic_error("Error in function" \
        "TArchive<T>& insert(const T* arr, size_t n, size_t pos)\":"
        " wrong position value.");
    }
    _states[_size - 1] = State::empty;
    --_size;
}

template <typename T>
TDMassive<T>& TDMassive<T> ::remove_by_index(size_t pos) {
    if (_size <= pos || pos < 0) {
        throw std::logic_error("Error in function" \
                               "void TArchive<T>::pop_back()\":"
                               " archive clear");
    }
    _states[pos] = State::deleted;
    _deleted++;
    return *this;
}

template <typename T>
TDMassive<T>& TDMassive<T>::erase(size_t pos, size_t n) {
    if (_size < pos) {
        throw std::logic_error("Error in function"\
        "TArchive<T>& TArchive<T>::erase(size_t pos, size_t n)\":"
        "wrong position value.");
    }
    for (size_t i = pos; i < pos + n; i++) {
        _states[i] = State::deleted;
    }
    _deleted = n;
}

template <typename T>
TDMassive<T>& TDMassive<T>::remove_all(T value) {
    if (_size <= 0) {
        throw std::logic_error("Error in function" \
        "TArchive<T>& TArchive<T>::remove_all(T value)\":"
        "archive clear");
    }
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value) {
            _states[i] = State::deleted;
            _deleted++;
        }
    }
}

template <typename T>
TDMassive<T>& TDMassive<T>::remove_first(T value) {
    if (_size <= 0) {
        throw std::logic_error("Error in function" \
        "TArchive<T>& TArchive<T>::remove_first(T value)\":"
        "archive clear");
    }
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value) {
            _states[i] = State::deleted;
            break;
        }
    }
    _deleted++;
}

template <typename T>
TDMassive<T>& TDMassive<T>::remove_last(T value) {
    if (_size <= 0) {
        throw std::logic_error("Error in function" \
        "TArchive<T>& TArchive<T>::remove_last(T value)\":"
        "archive clear");
    }
    for (size_t i = _size; i > 0; i--) {
        if (_data[i] == value) {
            _states[i] = State::deleted;
            break;
        }
    }
    _deleted++;
}

template <typename T>
size_t TDMassive<T>::find_first(T value) const {
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value && _states[i] != State::deleted) {
            return i;
        }
    }
    throw std::logic_error("Error in function" \
    "size_t TArchive<T>::find_first(T value)\":No mathes");
}


template <typename T>
size_t TDMassive<T>::find_last(T value) const {
    for (size_t i = _size; i > 0; i--) {
        if (_data[i] == value && _states[i] != State::deleted) {
            return i;
        }
    }
    throw std::logic_error("Error in function" \
    "size_t TArchive<T>::find_first(T value)\":No mathes");
}

template <typename T>
size_t* TDMassive<T>::find_all(T value) const noexcept {
    size_t count = this->count_value(value);
    if (count == 0) { return nullptr; }
    size_t* found_positions = new size_t[count + 1];
    found_positions[0] = count;
    size_t found_count = 0;

    for (size_t i = 0; i < _size; ++i) {
        if (_data[i] == value && _states[i] != State::deleted) {
            found_positions[++found_count] = i;
        }
    }

    return found_positions;
}

template <typename T>
TDMassive<T>& TDMassive<T>::replace(size_t pos, T new_value) {
    if (_states[pos] != State::busy) {
        throw std::logic_error("Error in function" \
        "TArchive<T>& replace(size_t pos, T new_value)\":"
        "No mathes");
    }
    if (pos >= _size) {
        throw std::logic_error("Error in function" \
        "TArchive<T>& replace(size_t pos, T new_value)\":"
        "Invalid position");
    }
    _data[pos] = new_value;
    _states[pos] = State::busy;
    return *this;
}

template <typename T>
void TDMassive<T>::print() const noexcept {
    for (size_t i = 0; i < _size; i++) {
        if (_states[i] != State::deleted) {
            std::cout << _data[i] << ", ";
        }
    }
}

template <typename T>
size_t TDMassive<T>::count_value(T value) const noexcept {
    size_t count = 0;
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == value) {
            count++;
        }
    }
    return count;
}

template <typename T>
T& TDMassive<T>::operator[](size_t index) {
    return _data[index];
}

template <typename T>
const T& TDMassive<T>::operator[](size_t index) const {
    return _data[index];
}
