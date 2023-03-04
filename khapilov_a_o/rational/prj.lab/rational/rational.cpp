#include <rational/rational.hpp>
#include <iostream>

Rational::Rational() {
    num = 0;
    denom = 1;
}
Rational::Rational(int32_t numInp) {
    num = numInp;
    denom = 1;
}
Rational::Rational(int32_t numInp, int32_t denomInp) {
    if (denomInp < 0) {
        denomInp *= -1;
        numInp *= -1;
    }
    if (denomInp == 0) {
        throw std::invalid_argument("Divide by zero exception");
    }
    num = numInp;
    denom = denomInp;
    redusing();
}

Rational& Rational::operator=(const Rational& rhs) {
    num = rhs.num;
    denom = rhs.denom;
    return *this;
}
Rational& Rational::operator+=(const Rational& rhs) {
    int32_t mult = rhs.denom / gcd(denom, rhs.denom);
    num *= mult;
    denom *= mult;
    num += denom / rhs.denom * rhs.num;
    redusing();
    return *this;
}
Rational& Rational::operator-=(const Rational& rhs) {
    int32_t mult = rhs.denom / gcd(denom, rhs.denom);
    num *= mult;
    denom *= mult;
    num -= denom / rhs.denom * rhs.num;
    redusing();
    return *this;
}
Rational& Rational::operator*=(const Rational& rhs) {
    num *= rhs.num;
    denom *= rhs.denom;
    redusing();
    return *this;
}
Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.isZero()) {
        throw std::invalid_argument("Divide by zero exception");
    }
    num *= rhs.denom;
    denom *= rhs.num;
    redusing();
    return *this;
}

Rational& Rational::operator++() {
    *this += 1;
    return *this;
}
Rational Rational::operator++(int) {
    Rational tmp(*this);
    ++(*this);
    return tmp;
}
Rational& Rational::operator--() {
    *this -= 1;
    return *this;
}
Rational Rational::operator--(int) {
    Rational tmp(*this);
    --(*this);
    return tmp;
}

Rational& Rational::operator%=(const Rational& rhs) {
    int32_t mult = rhs.denom / gcd(denom, rhs.denom);
    num *= mult;
    denom *= mult;
    num %= denom / rhs.denom * rhs.num;
    redusing();
    return *this;
}

bool Rational::isPositive() const {
    return num > 0;
}
bool Rational::isZero() const {
    return num == 0;
}
bool Rational::isNegative() const {
    return num < 0;
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
    return rhs.writeTo(ostrm);
}
std::istream& operator>>(std::istream& istrm, Rational& rhs) {
    return rhs.readFrom(istrm);
}

Rational& operator+(Rational& rhs) {
    return rhs;
}
Rational& operator-(Rational& rhs) {
    Rational tmp;
    tmp -= rhs;
    return tmp;
}

Rational operator+(Rational lhs, const Rational& rhs) {
    lhs += rhs;
    return lhs;
}
Rational operator-(Rational lhs, const Rational& rhs) {
    lhs -= rhs;
    return lhs;
}
Rational operator*(Rational lhs, const Rational& rhs) {
    lhs *= rhs;
    return lhs;
}
Rational operator/(Rational lhs, const Rational& rhs) {
    lhs /= rhs;
    return lhs;
}
Rational sqr(Rational myRat) {
    myRat *= myRat;
    return myRat;
}
Rational pow(Rational myRat, int32_t power) {
    Rational answer(1);
    if (power < 0) {
        myRat = Rational(1, 1) / myRat;
        power = -power;
    }
    while (power) {
        if (power & 1) {
            answer *= myRat;
        }
        myRat = sqr(myRat);
        power >>= 1;
    }
    return answer;
}

Rational operator%(Rational lhs, const Rational& rhs)
{
    lhs %= rhs;
    return lhs;
}

bool operator==(Rational lhs, const Rational& rhs) {
    lhs -= rhs;
    return lhs.isZero();
}
bool operator>(Rational lhs, const Rational& rhs) {
    Rational diff = lhs - rhs;
    return diff.Rational::isPositive();
}
bool operator<(Rational lhs, const Rational& rhs) {
    Rational diff = lhs - rhs;
    return diff.Rational::isNegative();
}
bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !operator==(lhs, rhs);
}
bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !operator>(lhs, rhs);
}
bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !operator<(lhs, rhs);
}

int32_t Rational::gcd(int32_t a, int32_t b) const {
    while (a != 0) {
        if (a < b) {
            std::swap(a, b);
        }
        a %= b;
    }
    return b;
}

void Rational::redusing() {
    int32_t dev = gcd(std::abs(num), denom);
    num /= dev;
    denom /= dev;
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const
{
    ostrm << num << slash << denom;
    return ostrm;
}

std::istream& Rational::readFrom(std::istream& istrm)
{
    int32_t numInp(0);
    char separator(0);
    int32_t denomInp(0);
    istrm >> numInp >> separator >> denomInp;
    if (istrm.good()) {
        if (Rational::slash == separator) {
            if (denomInp <= 0) {
                throw std::invalid_argument("Expected positive denomerator");
            }
            num = numInp;
            denom = denomInp;
            redusing();
        }
        else {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}