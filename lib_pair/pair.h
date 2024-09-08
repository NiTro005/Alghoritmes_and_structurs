// Copyright 2024 Marina Usova

#ifndef LIB_PAIR_PAIR_H_
#define LIB_PAIR_PAIR_H_

#include <iostream>
#include <string>
#include <stdexcept>

template <class T1, class T2> class TPair;
template <class T1, class T2>
std::ostream& operator<<(std::ostream& out, const TPair<T1, T2>& obj) noexcept;

template <class T1, class T2>
class TPair {
    T1 _first;
    T2 _second;
 public:
    TPair() : _first(NULL), _second(NULL) { }
    TPair(const T1& first, const T2& second) : _first(first), _second(second) { }
    TPair(const TPair& pair) : _first(pair._first), _second(pair._second) { }
    ~TPair() { }

    inline void set_first(const T1& value) noexcept;
    inline void set_second(const T2& value) noexcept;

    TPair& operator=(const TPair& pair) noexcept;
    TPair& operator+=(const TPair& pair) noexcept;
    TPair& operator-=(const TPair& pair) noexcept;
    TPair& operator*=(const TPair& pair) noexcept;
    TPair& operator/=(const TPair& pair) noexcept;

    TPair& operator+(const TPair& pair) const noexcept;
    TPair& operator-(const TPair& pair) const noexcept;
    TPair& operator/(const TPair& pair) const noexcept;
    TPair& operator*(const TPair& pair) const noexcept;

    std::string to_string() const noexcept;

    void swap(TPair& pair)noexcept;

    friend std::ostream& operator<< <T1, T2>(std::ostream& out, const TPair<T1, T2>& pair) noexcept;

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
TPair<T1, T2>& TPair<T1, T2>::operator=(const TPair<T1, T2>& pair) noexcept {
    if (this != &pair) {
        _first = pair._first;
        _second = pair._second;
    }
    return *this;
}

template <class T1, class T2>
TPair<T1, T2>& TPair<T1, T2>::operator-=(const TPair<T1, T2>& pair) noexcept {
    _first -= pair._first;
    _second -= pair._second;
    return *this;
}

template <class T1, class T2>
TPair<T1, T2>& TPair<T1, T2>::operator+=(const TPair<T1, T2>& pair) noexcept {
    _first += pair._first;
    _second += pair._second;
    return *this;
}

template <class T1, class T2>
TPair<T1, T2>& TPair<T1, T2>::operator+(const TPair<T1, T2>& pair) const noexcept {
    TPair<T1, T2> temp(*this);
    temp._first += pair._first;
    temp._second += pair._second;
    return temp;
}


template <class T1, class T2>
TPair<T1, T2>& operator-(const TPair<T1, T2>& pair1, const TPair<T1, T2>& pair2) noexcept {
    TPair<T1, T2> temp(*this);
    temp._first -= pair._first;
    temp._second -= pair._second;
    return temp;
}

template <class T1, class T2>
std::string TPair<T1, T2>::to_string() const noexcept {
    std::string str = "(" + std::to_string(_first) + ", " + std::to_string(_second) + ")";
    return str;
}

template <class T1, class T2>
std::ostream& operator<< <T1, T2>(std::ostream& out, const TPair<T1, T2>& pair) noexcept {
    out << pair.to_string();
    return out;
}

#endif  // LIB_PAIR_PAIR_H_
