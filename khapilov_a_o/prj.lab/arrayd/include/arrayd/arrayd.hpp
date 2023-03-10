#pragma once
#ifndef ARRAYD_ARRAYD_HPP_20230228
#define ARRAYD_ARRAYD_HPP_20230228

#include <iosfwd>
#include <cstdint>

class ArrayD{
public:
    ArrayD();
    ArrayD(const int32_t len);
    ArrayD(const ArrayD&);
    ArrayD(ArrayD&&) = default;
    ArrayD(int32_t sizeInp, int32_t number);

    ArrayD& operator=(const ArrayD& rhs);
    ArrayD& operator+=(const int32_t rhs);
    ArrayD& operator-=(const int32_t rhs);
    ArrayD& operator*=(const int32_t rhs);
    ArrayD& operator/=(const int32_t rhs);

    ArrayD& operator+();
    ArrayD& operator-();

    ArrayD& operator++();
    ArrayD operator++(int);
    ArrayD& operator--();
    ArrayD operator--(int);

    ArrayD& operator%=(const int32_t& rhs);

    std::ostream& writeTo(std::ostream& ostrm) const;
    /*std::istream& readFrom(std::istream& istrm);*/

public:
    int32_t size;
    int32_t* memory;

    static const char cmm{ ',' };
};

std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs);
//std::istream& operator>>(std::istream& istrm, ArrayD& rhs);

ArrayD operator+(ArrayD lhs, const int32_t rhs);
ArrayD operator-(ArrayD lhs, const int32_t rhs);
ArrayD operator*(ArrayD lhs, const int32_t rhs);
ArrayD operator/(ArrayD lhs, const int32_t rhs);

ArrayD operator%(ArrayD lhs, const int32_t& rhs);

bool operator==(ArrayD lhs, const ArrayD& rhs);
bool operator!=(const ArrayD& lhs, const ArrayD& rhs);

#endif
