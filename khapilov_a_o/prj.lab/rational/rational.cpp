#include <rational/rational.hpp>
#include <iostream>

Rational::Rational() {
    num_ = 0;
    denom_ = 1;
}
Rational::Rational(int32_t numInp_) noexcept{
    num_ = numInp_;
    denom_ = 1;
}
Rational::Rational(int32_t numInp_, int32_t denomInp_) {
    if (denomInp_ < 0) {
        denomInp_ *= -1;
        numInp_ *= -1;
    }
    if (denomInp_ == 0) {
        throw std::invalid_argument("Divide by zero exception");
    }
    num_ = numInp_;
    denom_ = denomInp_;
    redusing();
}

Rational& Rational::operator=(const Rational& rhs) {
    num_ = rhs.num_;
    denom_ = rhs.denom_;
    return *this;
}
Rational& Rational::operator+=(const Rational& rhs) {
    int32_t mult = rhs.denom_ / gcd(denom_, rhs.denom_);
    num_ *= mult;
    denom_ *= mult;
    num_ += denom_ / rhs.denom_ * rhs.num_;
    redusing();
    return *this;
}
Rational& Rational::operator-=(const Rational& rhs) {
    int32_t mult = rhs.denom_ / gcd(denom_, rhs.denom_);
    num_ *= mult;
    denom_ *= mult;
    num_ -= denom_ / rhs.denom_ * rhs.num_;
    redusing();
    return *this;
}
Rational& Rational::operator*=(const Rational& rhs) {
    num_ *= rhs.num_;
    denom_ *= rhs.denom_;
    redusing();
    return *this;
}
Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.IsZero()) {
        throw std::invalid_argument("Divide by zero exception");
    }
    num_ *= rhs.denom_;
    denom_ *= rhs.num_;
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
    int32_t mult = rhs.denom_ / gcd(denom_, rhs.denom_);
    num_ *= mult;
    denom_ *= mult;
    num_ %= denom_ / rhs.denom_ * rhs.num_;
    redusing();
    return *this;
}

bool Rational::IsPositive() const {
    return num_ > 0;
}
bool Rational::IsZero() const {
    return num_ == 0;
}
bool Rational::IsNegative() const {
    return num_ < 0;
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
    return rhs.WriteTo(ostrm);
}
std::istream& operator>>(std::istream& istrm, Rational& rhs) {
    return rhs.ReadFrom(istrm);
}

Rational operator+(const Rational& rhs) {
    return rhs;
}
Rational operator-(const Rational& rhs) {
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

Rational operator+(Rational lhs, const int32_t& rhs) {
    lhs += Rational(rhs);
    return lhs;
}
Rational operator-(Rational lhs, const int32_t& rhs) {
    lhs -= Rational(rhs);
    return lhs;
}
Rational operator*(Rational lhs, const int32_t& rhs) {
    lhs *= Rational(rhs);
    return lhs;
}
Rational operator/(Rational lhs, const int32_t& rhs) {
    lhs /= Rational(rhs);
    return lhs;
}

Rational operator+(const int32_t& lhs, Rational rhs) {
    rhs += lhs;
    return rhs;
}
Rational operator-(const int32_t& lhs, Rational rhs) {
    rhs -= lhs;
    return -rhs;
}
Rational operator*(const int32_t& lhs, Rational rhs) {
    rhs *= lhs;
    return rhs;
}
Rational operator/(const int32_t& lhs, Rational rhs) {
    rhs /= lhs;
    return pow(rhs, -1);
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

Rational operator%(const Rational& lhs, const Rational& rhs)
{
    Rational diff(lhs);
    diff %= rhs;
    return lhs;
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    Rational diff = lhs - rhs;
    return diff.IsZero();
}
bool operator>(const Rational& lhs, const Rational& rhs) {
    Rational diff = lhs - rhs;
    return diff.Rational::IsPositive();
}
bool operator<(const Rational& lhs, const Rational& rhs) {
    Rational diff = lhs - rhs;
    return diff.Rational::IsNegative();
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
    int32_t dev = gcd(std::abs(num_), denom_);
    num_ /= dev;
    denom_ /= dev;
}

std::ostream& Rational::WriteTo(std::ostream& ostrm) const noexcept
{
    ostrm << num_ << slash << denom_;
    return ostrm;
}

std::istream& Rational::ReadFrom(std::istream& istrm)
{
    char sym('-');
    while (std::isspace(istrm.peek())) {
        sym = istrm.get();
    }
    int32_t numInp_(0);
    int32_t denomInp_(0);
    sym = '-' ;
    bool isNeg(false);
    if (istrm.peek() == '-') {
        isNeg = true;
        sym = istrm.get();
    }

    while (std::isdigit(istrm.peek())) {
        sym = istrm.get();
        numInp_ *= 10;
        numInp_ += static_cast<int>(sym - '0');
    }
    if (sym == '-') {
        istrm.setstate(std::ios_base::failbit);
        return istrm;
    }

    if (istrm.peek() != '/') {
        istrm.setstate(std::ios_base::failbit);
        return istrm;
    }
    sym = istrm.get();

    while (std::isdigit(istrm.peek())) {
        sym = istrm.get();
        denomInp_ *= 10;
        denomInp_ += static_cast<int>(sym - '0');
    }
    if (sym == '/') {
        istrm.setstate(std::ios_base::failbit);
        return istrm;
    }
    
    if (istrm.good() || istrm.eof()) {
        if (denomInp_ == 0) {
            istrm.setstate(std::ios_base::failbit);
            return istrm;
        }
        num_ = numInp_;
        denom_ = denomInp_;
        if (isNeg) {
            num_ *= -1;
        }
        redusing();
    }
    return istrm;
}
