// Copyright 2024 Kita Trofimov
#pragma once
#include <iostream>
#include <vector>
#include "../lib_list/tlist.h"

#define MAX_COUNT 3

class CMonom {
 public:
    float _coef;
    int _powers[MAX_COUNT];

    CMonom(float coef = 1.0);
    CMonom(const CMonom& other);
    CMonom& operator=(const CMonom& other);

    bool operator==(const CMonom& other) const;
    bool operator!=(const CMonom& other) const;

    CMonom operator+(const CMonom& other) const;
    CMonom operator-(const CMonom& other) const;
    CMonom operator*(const CMonom& other) const;
    CMonom operator/(const CMonom& other) const;

    CMonom operator*(float scalar) const;
    CMonom operator/(float scalar) const;
    CMonom operator-() const;

    CMonom& operator+=(const CMonom& other);
    CMonom& operator-=(const CMonom& other);
    CMonom& operator*=(const CMonom& other);
    CMonom& operator/=(const CMonom& other);
    CMonom& operator*=(float scalar);
    CMonom& operator/=(float scalar);

    float evaluate(const std::vector<float>& values) const;

    friend std::ostream& operator<<(std::ostream& os, const CMonom& monom);
    friend std::istream& operator>>(std::istream& is, CMonom& monom);

    bool operator<(const CMonom& other) const;
};

class CPolynom {
 public:
    TList<CMonom> monoms;

    CPolynom();
    CPolynom(const std::string& polynomStr);
    CPolynom(const CPolynom& other);
    CPolynom& operator=(const CPolynom& other);

    CPolynom operator+(const CPolynom& other) const;
    CPolynom operator-(const CPolynom& other) const;
    CPolynom operator*(float scalar) const;
    CPolynom operator/(float scalar) const;

    CPolynom& operator+=(const CPolynom& other);
    CPolynom& operator-=(const CPolynom& other);
    CPolynom& operator*=(float scalar);
    CPolynom& operator/=(float scalar);

    float evaluate(const std::vector<float>& values) const;

 private:
    void addMonom(const CMonom& monom);
    void parsePolynom(const std::string& polynomStr);
};

