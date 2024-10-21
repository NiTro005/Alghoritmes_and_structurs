// Copyright 2024 Kita Trofimov
#include "../lib_string/cstring.h"
#include <iostream>
#include <string>
#include <algorithm>

CString::CString() {
    _size = 0;
    _capacity = STEP_CAPACITY;
    _data = new char[_capacity];
    _data[0] = '\0';
}


CString::CString(const CString& str) {
    _size = str._size;
    _capacity = str._capacity;
    _data = new char[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = str._data[i];
    }
    _data[_size] = '\0';
}

CString::CString(const char* c_str, size_t n) {
    _size = n;
    _capacity = (n / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = c_str[i];
    }
    _data[_size] = '\0';
}

CString::CString(const char* c_str) {
    _size = 0;
    while (c_str[_size] != '\0') {
        _size++;
    }
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = c_str[i];
    }
    _data[_size] = '\0';
}

CString:: CString(size_t n, char c) {
    _size = n;
    _capacity = (n / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = c;
    }
    _data[_size] = '\0';
}

CString::CString(const CString& str, size_t pos, size_t len) {
    _size = len;
    _capacity = (_size / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    _data = new char[_capacity];
    for (int i = pos; i < pos + len; i++) {
        _data[i - pos] = str._data[i];
    }
    _data[_size] = '\0';
}


CString::~CString() {
    delete[] _data;
    _data = nullptr;
}


bool CString::empty() const noexcept {
    return _size == 0;
}

bool CString::full() const noexcept {
    return _size == _capacity;
}

size_t CString::size() const noexcept {
    return _size;
}

size_t CString::capacity() const noexcept {
    return _capacity;
}


const char* CString::data() const {
    return _data;
}

void CString::swap(CString& str) {
    char* temp = this->_data;
    this->_data = str._data;
    str._data = temp;
}

size_t CString::copy(char* buf, size_t len, size_t pos) const {
    if (pos >= _size) {
        return 0;
    }

    size_t chars_to_copy = algorithms::min(len, _size - pos);
    std::memcpy(buf, _data + pos, chars_to_copy);
    return chars_to_copy;
}

CString CString:: substr(size_t pos, size_t len) const {
    if (pos >= _size) {
        return CString("");
    }

    len = std::min(len, _size - pos);

    char* substr_data = new char[len + 1];
    memcpy(substr_data, _data + pos, len);
    substr_data[len] = '\0';

    return CString(substr_data);
}

CString& CString:: assign(const CString& str) {
    _size = str._size;
    _capacity = str._capacity;
    _data = new char[_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = str._data[i];
    }
    _data[_size] = '\0';
    return *this;
}

int CString::compare(const CString& str) const noexcept {
    for (size_t i = 0; i < algorithms::min
    (_size, str._size); i++) {
        if (this->_data[i] < str._data[i]) {
            return 1;
        } else if (this->_data[i] > str._data[i]) {
            return -1;
        }
    }
    if (this->_size > str._size) {
        return 1;
    } else if (this->_size < str._size) {
        return -1;
    } else {
        return 0;
    }
}

void CString:: clear() noexcept {
    delete[] _data;
    _size = 0;
    _capacity = 0;
    _data[_size] = '\0';
}

void CString::resize(size_t n, char c) {
    if (n <= _size) {
        _data[n] = '\0';
        _size = n;
    } else {
        reserve(n);
        for (size_t i = _size; i < n; ++i) {
            _data[i] = c;
        }
        _data[n] = '\0';
        _size = n;
    }
}

void CString::reserve(size_t n) {
    if (n < _capacity) {
        return;
    }
    _capacity = (n / STEP_CAPACITY) * STEP_CAPACITY + STEP_CAPACITY;
    char* newData = new char[_capacity];
    std::memcpy(newData, _data, _size);
    delete[] _data;
    _data = newData;
}

void CString::push_back(char c) {
    if (this->full()) {
        this->reserve(_capacity);
    }

    _data[_size] = c;
    _data[++_size] = '\0';
}

void CString::pop_back() {
    if (this->empty()) {
        throw std::logic_error("Error in function" \
        "void pop_back()\": source CString is empty");
    }
    _data[--_size] = '\0';
}

CString& CString::erase(size_t pos, size_t len) {
    if (pos >= _size) {
        return *this;
    }
    len = std::min(len, _size - pos);
    if (len > 0) {
        size_t new_len = _size - len;
        memmove(_data + pos, _data + pos + len,
            new_len - pos);
        _size = new_len;
        _data[_size] = '\0';
    }

    return *this;
}

CString& CString::append(const CString& str) {
    if ((_capacity - _size) <= str._size) {
        reserve(_size + str._size);
    }
    for (int i = 0; i < str._size; ++i) {
        _data[_size + i] = str._data[i];
    }
    _size += str._size;
    return *this;
}

CString& CString::insert(size_t pos, const CString& str) {
    CString begin(*this, 0, pos);
    CString end(*this, pos, _size - pos);
    begin.append(str);
    begin.append(end);
    this->swap(begin);
    return *this;
}

CString& CString::replace(size_t pos,
    size_t len, const CString& str) {
    len = std::min(len, _size - pos);
    for (size_t i = pos; i < pos + len; i++) {
        if (str._data[i - pos] == '\0') {
            break;
        }
        _data[i] = str._data[i - pos];
    }
    return *this;
}

size_t CString::find(const CString& str,
    size_t pos) const {
    if (pos >= _size) {
        throw std::logic_error("Error in function \ Position > size");
    }
    for (size_t i = pos; i <= _size - str._size; i++) {
        for (size_t j = 0; j < str._size; j++) {
            if (_data[i + j] == str._data[j]) {
                return i;
            }
        }
    }
    return -1;
}

size_t CString::find_first_of
(const CString& str, size_t pos) const {
    for (size_t i = pos; i < _size; i++) {
        for (size_t j = 0; j < str._size; j++) {
            if (_data[i] == str._data[j]) {
                return i;
            }
        }
    }
    return -1;
}

size_t CString::find_first_not_of
(const CString& str, size_t pos) const {
    for (size_t i = pos; i < _size; i++) {
        bool found = false;
        for (size_t j = 0; j < str._size; j++) {
            if (_data[i] == str._data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            return i;
        }
    }
    return -1;
}

void CString::print(size_t pos,
    size_t len) const noexcept {
    for (int i = pos; i < _size - pos + len; i++) {
        std::cout << _data[i];
    }
}

CString& CString::append
(const CString& str, size_t subpos, size_t sublen) {
    if (subpos >= str._size) return *this;

    size_t new_size = _size + sublen;
    reserve(new_size);

    for (size_t i = 0; i < sublen; ++i) {
        _data[_size++] = str._data[subpos + i];
    }

    _data[_size] = '\0';
    return *this;
}

CString& CString::append(const char* s) {
    if (s == nullptr) return *this;

    size_t len = strlen(s);
    size_t new_size = _size + len;
    reserve(new_size);

    for (size_t i = 0; i < len; ++i) {
        _data[_size++] = s[i];
    }

    _data[_size] = '\0';
    return *this;
}

CString& CString::append(const char* s, size_t n) {
    if (s == nullptr) return *this;

    size_t len = strlen(s);
    size_t actual_len = std::min(len, n);
    size_t new_size = _size + actual_len;
    reserve(new_size);

    for (size_t i = 0; i < actual_len; ++i) {
        _data[_size++] = s[i];
    }

    _data[_size] = '\0';
    return *this;
}

CString& CString::append(size_t n, char c) {
    size_t new_size = _size + n;
    reserve(new_size);

    for (size_t i = 0; i < n; ++i) {
        _data[_size++] = c;
    }

    _data[_size] = '\0';
    return *this;
}

CString& CString::insert(size_t pos,
    const CString& str, size_t subpos,
    size_t sublen) {
    if (pos > _size || subpos >= str._size) {
        return *this;
    }
    size_t new_size = _size + sublen;
    reserve(new_size);

    for (size_t i = _size; i > pos; --i) {
        _data[i + sublen - 1] = _data[i - 1];
    }

    for (size_t i = 0; i < sublen; ++i) {
        _data[pos + i] = str._data[subpos + i];
    }

    _size = new_size;
    _data[_size] = '\0';
    return *this;
}

CString& CString::insert(size_t pos,
    const char* s) {
    if (pos > _size || s == nullptr) return *this;

    size_t len = strlen(s);
    size_t new_size = _size + len;
    reserve(new_size);

    for (size_t i = _size; i > pos; --i) {
        _data[i + len - 1] = _data[i - 1];
    }

    for (size_t i = 0; i < len; ++i) {
        _data[pos + i] = s[i];
    }

    _size = new_size;
    _data[_size] = '\0';
    return *this;
}

CString& CString::insert(size_t pos,
    const char* s, size_t n) {
    if (pos > _size || s == nullptr) return *this;

    size_t len = strlen(s);
    size_t actual_len = std::min(len, n);
    size_t new_size = _size + actual_len;
    reserve(new_size);

    for (size_t i = _size; i > pos; --i) {
        _data[i + actual_len - 1] = _data[i - 1];
    }

    for (size_t i = 0; i < actual_len; ++i) {
        _data[pos + i] = s[i];
    }

    _size = new_size;
    _data[_size] = '\0';
    return *this;
}

CString& CString::insert(size_t pos,
    size_t n, char c) {
    if (pos > _size) return *this;

    size_t new_size = _size + n;
    reserve(new_size);

    for (size_t i = _size; i > pos; --i) {
        _data[i + n - 1] = _data[i - 1];
    }

    for (size_t i = 0; i < n; ++i) {
        _data[pos + i] = c;
    }

    _size = new_size;
    _data[_size] = '\0';
    return *this;
}

CString& CString::replace(size_t pos, size_t len,
    const CString& str, size_t subpos, size_t sublen) {
    if (pos >= _size) return *this;

    size_t new_size = _size - len + sublen;
    reserve(new_size);

    for (size_t i = pos + len; i < _size; ++i) {
        _data[i + sublen - len] = _data[i];
    }

    for (size_t i = 0; i < sublen; ++i) {
        _data[pos + i] = str._data[subpos + i];
    }

    _size = new_size;
    _data[_size] = '\0';
    return *this;
}

CString& CString::replace(size_t pos,
    size_t len, const char* s, size_t n) {
    if (pos >= _size) return *this;

    size_t new_size = _size - len + n;
    reserve(new_size);

    for (size_t i = pos + len; i < _size; ++i) {
        _data[i + n - len] = _data[i];
    }

    for (size_t i = 0; i < n; ++i) {
        _data[pos + i] = s[i];
    }

    _size = new_size;
    _data[_size] = '\0';
    return *this;
}

CString& CString::replace(size_t pos,
    size_t len, size_t n, char c) {
    if (pos >= _size) return *this;

    size_t new_size = _size - len + n;
    reserve(new_size);

    for (size_t i = pos + len; i < _size; ++i) {
        _data[i + n - len] = _data[i];
    }

    for (size_t i = 0; i < n; ++i) {
        _data[pos + i] = c;
    }

    _size = new_size;
    _data[_size] = '\0';
    return *this;
}

size_t CString::find(const char* s,
    size_t pos) const {
    if (s == nullptr || pos >= _size) return std::string::npos;

    char* found = strstr(_data + pos, s);
    if (found == nullptr) return std::string::npos;

    return found - _data;
}

size_t CString::find(const char* s,
    size_t pos, size_t n) const {
    if (s == nullptr || pos >= _size) {
        return std::string::npos;
    }
    char* found = nullptr;
    for (size_t i = pos; i <= _size - n; ++i) {
        if (strncmp(_data + i, s, n) == 0) {
            found = _data + i;
            break;
        }
    }

    if (found == nullptr) return std::string::npos;
    return found - _data;
}

size_t CString::find(char c, size_t pos) const {
    if (pos >= _size) return std::string::npos;

    char* found = strchr(_data + pos, c);
    if (found == nullptr) return std::string::npos;

    return found - _data;
}

size_t CString::find_first_of
(const char* s, size_t pos) const {
    if (s == nullptr || pos >= _size) {
        return std::string::npos;
    }
    char* found = strpbrk(_data + pos, s);
    if (found == nullptr) return std::string::npos;

    return found - _data;
}

size_t CString::find_first_of
(const char* s, size_t pos, size_t n) const {
    if (s == nullptr || pos >= _size) {
        return std::string::npos;
    }

    for (size_t i = pos; i < _size; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (_data[i] == s[j]) {
                return i;
            }
        }
    }

    return std::string::npos;
}

size_t CString::find_first_of
(char c, size_t pos) const {
    if (pos >= _size) return std::string::npos;

    char* found = strchr(_data + pos, c);
    if (found == nullptr) return std::string::npos;

    return found - _data;
}

size_t CString::find_first_not_of
(const char* s, size_t pos) const {
    if (s == nullptr || pos >= _size) {
        return std::string::npos;
    }

    for (size_t i = pos; i < _size; ++i) {
        if (strchr(s, _data[i]) == nullptr) {
            return i;
        }
    }

    return std::string::npos;
}

size_t CString::find_first_not_of
(const char* s, size_t pos, size_t n) const {
    if (s == nullptr || pos >= _size) {
        return std::string::npos;
    }

    for (size_t i = pos; i < _size; ++i) {
        bool found = false;
        for (size_t j = 0; j < n; ++j) {
            if (_data[i] == s[j]) {
                found = true;
                break;
            }
        }
        if (!found) return i;
    }
    return std::string::npos;
}

size_t CString::find_first_not_of
(char c, size_t pos) const {
    if (pos >= _size) return std::string::npos;

    for (size_t i = pos; i < _size; ++i) {
        if (_data[i] != c) {
            return i;
        }
    }
    return std::string::npos;
}

CString& CString::assign(const CString& str,
    size_t pos, size_t len) {
    if (pos >= str.size()) {
        throw std::out_of_range("Position out of range");
    }

    if (len == 0) {
        clear();
        return *this;
    }

    if (pos + len > str.size()) {
        len = str.size() - pos;
    }

    if (len > _max_capacity) {
        throw std::length_error("Length exceeds maximum capacity");
    }

    if (_data) {
        delete[] _data;
    }

    _size = len;
    _capacity = len + 1;
    _data = new char[_capacity];

    std::memcpy(_data, str._data + pos, len);
    _data[len] = '\0';

    return *this;
}

CString& CString::assign(const char* s) {
    size_t len = std::strlen(s);

    if (len > _max_capacity) {
        throw std::length_error
        ("Length exceeds maximum capacity");
    }

    if (_data) {
        delete[] _data;
    }

    _size = len;
    _capacity = len + 1;
    _data = new char[_capacity];

    std::memcpy(_data, s, len);
    _data[len] = '\0';

    return *this;
}

CString& CString::assign(const char* s, size_t n) {
    if (n > _max_capacity) {
        throw std::length_error
        ("Length exceeds maximum capacity");
    }

    if (_data) {
        delete[] _data;
    }

    _size = n;
    _capacity = n + 1;
    _data = new char[_capacity];

    std::memcpy(_data, s, n);
    _data[n] = '\0';

    return *this;
}

CString& CString::assign(size_t n, char c) {
    if (n > _max_capacity) {
        throw std::length_error
        ("Length exceeds maximum capacity");
    }

    if (_data) {
        delete[] _data;
    }

    _size = n;
    _capacity = n + 1;
    _data = new char[_capacity];

    std::memset(_data, c, n);
    _data[n] = '\0';

    return *this;
}


int CString::compare(size_t pos, size_t len,
    const CString& str) const {
    if (pos >= _size || pos + len > _size) {
        throw std::out_of_range
        ("Position and length are out of range");
    }

    return std::strncmp(_data + pos, str._data, len);
}

int CString::compare(size_t pos, size_t len,
    const CString& str, size_t subpos,
    size_t sublen) const {
    if (pos >= _size || pos + len > _size ||
        subpos >= str._size ||
        subpos + sublen > str._size) {
        throw std::out_of_range
        ("Position and length are out of range");
    }

    return std::strncmp
    (_data + pos, str._data + subpos,
        std::min(len, sublen));
}

int CString::compare(const char* s) const {
    return std::strcmp(_data, s);
}

int CString::compare(size_t pos,
    size_t len, const char* s) const {
    if (pos >= _size || pos + len > _size) {
        throw std::out_of_range
        ("Position and length are out of range");
    }

    return std::strncmp(_data + pos, s, len);
}

int CString::compare(size_t pos, size_t len,
    const char* s, size_t n) const {
    if (pos >= _size || pos + len > _size) {
        throw std::out_of_range
        ("Position and length are out of range");
    }

    return std::strncmp(_data + pos, s,
        std::min(len, n));
}

char& CString::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

const char& CString::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}
