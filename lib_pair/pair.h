// Copyright 2024 Marina Usova
#pragma once
#ifndef LIB_PAIR_PAIR_H_
#define LIB_PAIR_PAIR_H_

#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

template <class T1, class T2> class TPair;
template <class T1, class T2>
std::ostream& operator<<(std::ostream& out, const TPair<T1, T2>& pair) noexcept;
template <class T1, class T2>
std::istream& operator>>(std::istream& in,
    TPair<T1, T2>& obj) noexcept;  // NOLINT(runtime/references)

template <class T1, class T2>
class TPair {
    T1 _first;
    T2 _second;

 public:
    TPair() = default;
    TPair(const T1& first, const T2& second)
        : _first(first), _second(second) { }
    TPair(const TPair& pair) : _first(pair._first), _second(pair._second) { }
    ~TPair() { }

    inline T1 first() const noexcept;
    inline T2 second() const noexcept;

    inline void set_first(const T1& value) noexcept;
    inline void set_second(const T2& value) noexcept;

    TPair& operator=(const TPair& pair) noexcept;
    bool operator==(const T1& key) const noexcept;
    bool operator==(const TPair<T1, T2>& other) const noexcept;
    bool operator!=(const TPair<T1, T2>& other) const noexcept;
    bool operator<(const T1& key) const noexcept;
    bool operator<(const TPair<T1, T2>& other) const noexcept;

    void swap(TPair& pair)noexcept;

    friend std::ostream& operator<< <T1, T2>(std::ostream& out,
        const TPair<T1, T2>& pair) noexcept;
    friend std::istream& operator>> <T1, T2>
        (std::istream& in,
            TPair<T1, T2>& obj) noexcept;  // NOLINT(runtime/references)
};


template <class T1, class T2>
inline void TPair<T1, T2>::set_first(const T1& value) noexcept {
    _first = value;
}

template <class T1, class T2>
inline void TPair<T1, T2>::set_second(const T2& value) noexcept {
    _second = value;
}

template <class T1, class T2>
inline T1 TPair<T1, T2>::first() const noexcept {
    return _first;
}

template <class T1, class T2>
inline T2 TPair<T1, T2>::second() const noexcept {
    return _second;
}

template <class T1, class T2>
TPair<T1, T2>& TPair<T1, T2>::operator=(const TPair<T1, T2>& pair) noexcept {
    if (this != &pair) {
        _first = pair._first;
        _second = pair._second;
    }
    return *this;
}

template <class T1, class T2>
bool TPair<T1, T2>::operator==(const T1& key) const noexcept {
    return _first == key;
}

template <class T1, class T2>
bool TPair<T1, T2>::operator==(const TPair<T1, T2>& other) const noexcept {
    return _first == other._first;
}

template <class T1, class T2>
bool TPair<T1, T2>::operator!=(const TPair<T1, T2>& other) const noexcept {
    return _first != other._first;
}

template <class T1, class T2>
bool TPair<T1, T2>::operator<(const T1& key) const noexcept {
    return _first < key;
}

template <class T1, class T2>
bool TPair<T1, T2>::operator<(const TPair<T1, T2>& other) const noexcept {
    return _first < other._first;
}

template <class T1, class T2>
void TPair<T1, T2>::swap(TPair& pair) noexcept {
    T1 tempF = pair._first;
    T2 tempS = pair._second;
    pair._first = _first;
    pair._second = _second;
    _first = tempF;
    _second = tempS;
}

template <class T1, class T2>
std::ostream& operator<< <T1, T2>
(std::ostream& out, const TPair<T1, T2>& pair) noexcept {
    out << pair._first << " " << pair._second;
    return out;
}

template <typename T1, typename T2>
std::istream& operator>>
(std::istream& in, TPair<T1, T2>& obj) noexcept {  // NOLINT(runtime/references)
    in >> obj._first >> obj._second;
    return in;
}

#endif  // LIB_PAIR_PAIR_H_
