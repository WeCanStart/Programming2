#pragma once
#ifndef ARRAYD_ARRAYD_HPP_20230228
#define ARRAYD_ARRAYD_HPP_20230228

#include <iosfwd>
#include <cstdint>

class ArrayD{
public:
    ArrayD();
    ArrayD(const std::ptrdiff_t len);
    ArrayD(const ArrayD&);
    ArrayD(const ArrayD&&) noexcept;
    ArrayD(std::ptrdiff_t sizeInp, double number);

    ~ArrayD();

    std::ptrdiff_t ssize() const;

    double& operator[](std::ptrdiff_t index);
    const double& operator[](std::ptrdiff_t index) const;

    void reserve(std::ptrdiff_t newCapacity_);
    void resize(std::ptrdiff_t newSsize_);

    void insert(std::ptrdiff_t, double num);
    void remove(std::ptrdiff_t);

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
    std::ptrdiff_t ssize_;
    std::ptrdiff_t capacity_;
    double* memory_;

    static const char cmm{ ',' };
};

std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs);
//std::istream& operator>>(std::istream& istrm, ArrayD& rhs);

ArrayD operator+(ArrayD lhs, const double rhs);
ArrayD operator-(ArrayD lhs, const double rhs);
ArrayD operator*(ArrayD lhs, const double rhs);
ArrayD operator/(ArrayD lhs, const double rhs);

bool operator==(const ArrayD& lhs, const ArrayD& rhs);
bool operator!=(const ArrayD& lhs, const ArrayD& rhs);

#endif
