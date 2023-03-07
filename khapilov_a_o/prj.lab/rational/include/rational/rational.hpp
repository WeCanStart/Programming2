#pragma once
#ifndef RATIONAL_RATIONAL_HPP_20230215
#define RATIONAL_RATIONAL_HPP_20230215

#include <iosfwd>
#include <cstdint>

class Rational{
  public:
      Rational();
      Rational(const int32_t numInp);
      Rational(const Rational&) = default;
      Rational(Rational&&) = default;
      Rational(int32_t numInp, int32_t denomInp);

      Rational& operator=(const Rational& rhs);
      Rational& operator+=(const Rational& rhs);
      Rational& operator-=(const Rational& rhs);
      Rational& operator*=(const Rational& rhs);
      Rational& operator/=(const Rational& rhs);

      Rational& operator++();
      Rational operator++(int);
      Rational& operator--();
      Rational operator--(int);

      Rational& operator%=(const Rational& rhs);

      bool isPositive() const;
      bool isZero() const;
      bool isNegative() const;

      std::ostream& writeTo(std::ostream& ostrm) const;
      std::istream& readFrom(std::istream& istrm);

private:
    int32_t gcd(int32_t a, int32_t b) const;
    void redusing();
private:
    int32_t num{ 0 };
    int32_t denom{ 1 };

    static const char slash{ '/' };
};

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);
std::istream& operator>>(std::istream& istrm, Rational& rhs);

Rational& operator+(Rational& rhs);
Rational& operator-(Rational& rhs);

Rational operator+(Rational lhs, const Rational& rhs);
Rational operator-(Rational lhs, const Rational& rhs);
Rational operator*(Rational lhs, const Rational& rhs);
Rational operator/(Rational lhs, const Rational& rhs);
Rational sqr(Rational myRat);
Rational pow(Rational myRat, const int32_t power);

Rational operator%(Rational lhs, const Rational& rhs);

bool operator==(Rational lhs, const Rational& rhs);
bool operator>(Rational lhs, const Rational& rhs);
bool operator<(Rational lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);

#endif
