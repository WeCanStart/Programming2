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
    ArrayD(ptrdiff_t sizeInp, int32_t number);

    ~ArrayD();

    int32_t& operator[](ptrdiff_t index);
    const int32_t& operator[](ptrdiff_t index) const;

    void reserve(ptrdiff_t newCapacity_);
    void resize(ptrdiff_t newSsize_);
    void push_back(int32_t newElement);
    int32_t pop_back();

    ArrayD& operator=(const ArrayD& rhs);
    ArrayD& operator+=(const int32_t rhs);
    ArrayD& operator-=(const int32_t rhs);
    ArrayD& operator*=(const int32_t rhs);
    ArrayD& operator/=(const int32_t rhs);

    ArrayD& operator+();
    ArrayD& operator-();

    ArrayD& operator%=(const int32_t& rhs);

    std::ostream& writeTo(std::ostream& ostrm) const;
    /*std::istream& readFrom(std::istream& istrm);*/

public:
    ptrdiff_t ssize_;
    ptrdiff_t capacity_;
    int32_t* memory_;

    static const char cmm{ ',' };
};

std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs);
//std::istream& operator>>(std::istream& istrm, ArrayD& rhs);

ArrayD operator+(ArrayD lhs, const int32_t rhs);
ArrayD operator-(ArrayD lhs, const int32_t rhs);
ArrayD operator*(ArrayD lhs, const int32_t rhs);
ArrayD operator/(ArrayD lhs, const int32_t rhs);

ArrayD operator%(ArrayD lhs, const int32_t& rhs);

bool operator==(const ArrayD& lhs, const ArrayD& rhs);
bool operator!=(const ArrayD& lhs, const ArrayD& rhs);

#endif
