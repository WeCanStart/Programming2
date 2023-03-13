#pragma once
#ifndef ARRAYD_ARRAYD_HPP_20230228
#define ARRAYD_ARRAYD_HPP_20230228

#include <iosfwd>
#include <cstdint>

class ArrayD{
public:
    ArrayD();
    ArrayD(const ptrdiff_t len);
    ArrayD(const ArrayD&);
    ArrayD(ArrayD&&) = default;
    ArrayD(ptrdiff_t sizeInp, double number);

    ~ArrayD();

    double& operator[](ptrdiff_t index);
    const double& operator[](ptrdiff_t index) const;

    void reserve(ptrdiff_t newCapacity_);
    void resize(ptrdiff_t newSsize_);
    void push_back(double newElement);
    double pop_back();

    ArrayD& operator=(const ArrayD& rhs);
    ArrayD& operator+=(const double rhs);
    ArrayD& operator-=(const double rhs);
    ArrayD& operator*=(const double rhs);
    ArrayD& operator/=(const double rhs);

    ArrayD& operator+();
    ArrayD& operator-();

    std::ostream& writeTo(std::ostream& ostrm) const;
    /*std::istream& readFrom(std::istream& istrm);*/

public:
    ptrdiff_t ssize_;
    ptrdiff_t capacity_;
    double* memory_;

    static const char cmm{ ',' };
};

std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs);
//std::istream& operator>>(std::istream& istrm, ArrayD& rhs);

ArrayD operator+(ArrayD lhs, const double rhs);
ArrayD operator-(ArrayD lhs, const double rhs);
ArrayD operator*(ArrayD lhs, const double rhs);
ArrayD operator/(ArrayD lhs, const double rhs);

ArrayD operator%(ArrayD lhs, const double& rhs);

bool operator==(const ArrayD& lhs, const ArrayD& rhs);
bool operator!=(const ArrayD& lhs, const ArrayD& rhs);

#endif
