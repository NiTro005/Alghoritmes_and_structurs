// Copyright 2024 Kita Trofimov
#include "../lib_polinom/polinom.h"

#include <cmath>
#include <sstream>
#include <algorithm>

CMonom::CMonom(float coef) : _coef(coef) {
    std::fill(std::begin(_powers), std::end(_powers), 0);
}

CMonom::CMonom(const CMonom& other) : _coef(other._coef) {
    std::copy(std::begin(other._powers), std::end(other._powers), std::begin(_powers));
}

CMonom& CMonom::operator=(const CMonom& other) {
    if (this != &other) {
        _coef = other._coef;
        std::copy(std::begin(other._powers), std::end(other._powers), std::begin(_powers));
    }
    return *this;
}

bool CMonom::operator==(const CMonom& other) const {
    return std::equal(std::begin(_powers), std::end(_powers), std::begin(other._powers));
}

bool CMonom::operator!=(const CMonom& other) const {
    return !(*this == other);
}

CMonom CMonom::operator+(const CMonom& other) const {
    if (*this != other) throw std::invalid_argument("Monomials are not similar");
    CMonom result(*this);
    result._coef += other._coef;
    return result;
}

CMonom CMonom::operator-(const CMonom& other) const {
    if (*this != other) throw std::invalid_argument("Monomials are not similar");
    CMonom result(*this);
    result._coef -= other._coef;
    return result;
}

CMonom CMonom::operator*(const CMonom& other) const {
    CMonom result(_coef * other._coef);
    for (int i = 0; i < MAX_COUNT; ++i) {
        result._powers[i] = _powers[i] + other._powers[i];
    }
    return result;
}

CMonom CMonom::operator/(const CMonom& other) const {
    if (other._coef == 0) throw std::invalid_argument("Division by zero");
    CMonom result(_coef / other._coef);
    for (int i = 0; i < MAX_COUNT; ++i) {
        result._powers[i] = _powers[i] - other._powers[i];
    }
    return result;
}

CMonom CMonom::operator*(float scalar) const {
    CMonom result(*this);
    result._coef *= scalar;
    return result;
}

CMonom CMonom::operator/(float scalar) const {
    if (scalar == 0) throw std::invalid_argument("Division by zero");
    CMonom result(*this);
    result._coef /= scalar;
    return result;
}

CMonom CMonom::operator-() const {
    CMonom result(*this);
    result._coef = -_coef;
    return result;
}

CMonom& CMonom::operator+=(const CMonom& other) {
    *this = *this + other;
    return *this;
}

CMonom& CMonom::operator-=(const CMonom& other) {
    *this = *this - other;
    return *this;
}

CMonom& CMonom::operator*=(const CMonom& other) {
    *this = *this * other;
    return *this;
}

CMonom& CMonom::operator/=(const CMonom& other) {
    *this = *this / other;
    return *this;
}

CMonom& CMonom::operator*=(float scalar) {
    *this = *this * scalar;
    return *this;
}

CMonom& CMonom::operator/=(float scalar) {
    *this = *this / scalar;
    return *this;
}

float CMonom::evaluate(const std::vector<float>& values) const {
    if (values.size() != MAX_COUNT) throw std::invalid_argument("Invalid number of variables");
    float result = _coef;
    for (int i = 0; i < MAX_COUNT; ++i) {
        result *= std::pow(values[i], _powers[i]);
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const CMonom& monom) {
    os << monom._coef;
    for (int i = 0; i < MAX_COUNT; ++i) {
        if (monom._powers[i] != 0) {
            os << "x" << i + 1 << "^" << monom._powers[i];
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, CMonom& monom) {
    std::string input;
    is >> input;
    std::istringstream iss(input);
    iss >> monom._coef;
    char var;
    int power;
    while (iss >> var >> power) {
        if (var >= 'x' && var <= 'z') {
            monom._powers[var - 'x'] = power;
        }
    }
    return is;
}

bool CMonom::operator<(const CMonom& other) const {
    for (int i = 0; i < MAX_COUNT; ++i) {
        if (_powers[i] < other._powers[i]) {
            return true;
        }
        else if (_powers[i] > other._powers[i]) {
            return false;
        }
    }
    return false;
}

CPolynom::CPolynom() {}

CPolynom::CPolynom(const CPolynom& other) : monoms(other.monoms) {}

CPolynom& CPolynom::operator=(const CPolynom& other) {
    if (this != &other) {
        monoms = other.monoms;
    }
    return *this;
}

CPolynom CPolynom::operator+(const CPolynom& other) const {
    CPolynom result = *this;
    result += other;
    return result;
}

CPolynom CPolynom::operator-(const CPolynom& other) const {
    CPolynom result = *this;
    result -= other;
    return result;
}

CPolynom CPolynom::operator*(float scalar) const {
    CPolynom result = *this;
    result *= scalar;
    return result;
}

CPolynom CPolynom::operator/(float scalar) const {
    CPolynom result = *this;
    result /= scalar;
    return result;
}

CPolynom& CPolynom::operator+=(const CPolynom& other) {
    for (auto it = other.monoms.begin(); it != other.monoms.end(); ++it) {
        addMonom(*it);
    }
    return *this;
}

CPolynom& CPolynom::operator-=(const CPolynom& other) {
    for (auto it = other.monoms.begin(); it != other.monoms.end(); ++it) {
        addMonom(-*it);
    }
    return *this;
}

CPolynom& CPolynom::operator*=(float scalar) {
    for (auto& monom : monoms) {
        monom *= scalar;
    }
    return *this;
}

CPolynom& CPolynom::operator/=(float scalar) {
    for (auto& monom : monoms) {
        monom /= scalar;
    }
    return *this;
}

float CPolynom::evaluate(const std::vector<float>& values) const {
    float result = 0;
    for (const auto& monom : monoms) {
        result += monom.evaluate(values);
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const CPolynom& polynom) {
    for (auto it = polynom.monoms.begin(); it != polynom.monoms.end(); ++it) {
        os << *it;
        auto nextIt = it;
        ++nextIt;
        if (nextIt != polynom.monoms.end()) {
            os << " + ";
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, CPolynom& polynom) {
    std::string input;
    is >> input;
    std::istringstream iss(input);
    CMonom monom;
    while (iss >> monom) {
        polynom.addMonom(monom);
    }
    return is;
}

void CPolynom::addMonom(const CMonom& monom) {
    for (auto it = monoms.begin(); it != monoms.end(); ++it) {
        if (*it == monom) {
            *it += monom;
            return;
        }
    }

    auto it = monoms.begin();
    while (it != monoms.end() && *it < monom) {
        ++it;
    }
    monoms.insert(it.getNode(), monom);
}
