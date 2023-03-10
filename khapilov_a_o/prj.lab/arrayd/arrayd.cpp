#include <arrayd/arrayd.hpp>
#include <iostream>
#include <string>
#include <sstream>

ArrayD::ArrayD() {
    memory = nullptr;
    size = 0;
}
ArrayD::ArrayD(const ArrayD& prev) {
    size = prev.size;
    memory = new int32_t[size];
    for (int i = 0; i < size; ++i) {
        memory[i] = prev.memory[i];
    }
}
ArrayD::ArrayD(int32_t sizeInp) {
    size = sizeInp;
    memory = new int32_t[size];
    for (int i = 0; i < size; ++i) {
        memory[i] = 0;
    }
}
ArrayD::ArrayD(int32_t sizeInp, int32_t num) {
    size = sizeInp;
    memory = new int32_t[size];
    for (int i = 0; i < size; ++i) {
        memory[i] = num;
    }
}

ArrayD& ArrayD::operator=(const ArrayD& rhs) {
    size = rhs.size;
    memory = new int32_t[size];
    for (int i = 0; i < size; ++i) {
        memory[i] = rhs.memory[i];
    }
    return *this;
}
ArrayD& ArrayD::operator+=(const int32_t rhs) {
    for (int i = 0; i < size; ++i) {
        memory[i] += rhs;
    }
    return *this;
}
ArrayD& ArrayD::operator-=(const int32_t rhs) {
    for (int i = 0; i < size; ++i) {
        memory[i] -= rhs;
    }
    return *this;
}
ArrayD& ArrayD::operator*=(const int32_t rhs) {
    for (int i = 0; i < size; ++i) {
        memory[i] *= rhs;
    }
    return *this;
}
ArrayD& ArrayD::operator/=(const int32_t rhs) {
    if (rhs == 0) {
        throw std::invalid_argument("Divide by zero exception");
    }
    for (int i = 0; i < size; ++i) {
        memory[i] /= rhs;
    }
    return *this;
}

ArrayD& ArrayD::operator+() {
    return *this;
}
ArrayD& ArrayD::operator-() {
    for (int i = 0; i < size; ++i) {
        memory[i] = -memory[i];
    }
    return *this;
}

ArrayD& ArrayD::operator++() {
    *this += 1;
    return *this;
}
ArrayD ArrayD::operator++(int) {
    ArrayD tmp(*this);
    ++(*this);
    return tmp;
}
ArrayD& ArrayD::operator--() {
    *this -= 1;
    return *this;
}
ArrayD ArrayD::operator--(int) {
    ArrayD tmp(*this);
    --(*this);
    return tmp;
}

ArrayD& ArrayD::operator%=(const int32_t& rhs) {
    if (rhs == 0) {
        throw std::invalid_argument("Divide by zero exception");
    }
    for (int i = 0; i < size; ++i) {
        memory[i] %= rhs;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs) {
    return rhs.writeTo(ostrm);
}
//std::istream& operator>>(std::istream& istrm, ArrayD& rhs) {
//    return rhs.readFrom(istrm);
//}

ArrayD operator+(ArrayD lhs, const int32_t rhs) {
    lhs += rhs;
    return lhs;
}
ArrayD operator-(ArrayD lhs, const int32_t rhs) {
    lhs -= rhs;
    return lhs;
}
ArrayD operator*(ArrayD lhs, const int32_t rhs) {
    lhs *= rhs;
    return lhs;
}
ArrayD operator/(ArrayD lhs, const int32_t rhs) {
    lhs /= rhs;
    return lhs;
}

ArrayD operator%(ArrayD lhs, const int32_t& rhs)
{
    lhs %= rhs;
    return lhs;
}

bool operator==(ArrayD lhs, const ArrayD& rhs) {
    if (lhs.size != rhs.size) {
        return false;
    }
    bool isEqual = true;
    for (int i = 0; i < lhs.size; ++i) {
        isEqual *= (lhs.memory[i] == rhs.memory[i]);
    }
    return isEqual;
}

bool operator!=(const ArrayD& lhs, const ArrayD& rhs) {
    return !operator==(lhs, rhs);
}

std::ostream& ArrayD::writeTo(std::ostream& ostrm) const
{
    ostrm << '[';
    for (int i = 0; i < size - 1; ++i) {
        ostrm << memory[i] << cmm;
    }
    ostrm << memory[size - 1] << ']';
    return ostrm;
}

//std::istream& ArrayD::readFrom(std::istream& istrm)
//{
//    int32_t numInp(0);
//    char sym(0);
//    istrm >> sym;
//    std::istringstream input;
//    for (int i = 0; i < size; ++i) {
//        istrm >> sym >> input;
//    }
//    
//    if (istrm.good()) {
//        if (ArrayD::cmm == sym) {
//            if (denomInp <= 0) {
//                throw std::invalid_argument("Expected positive denomerator");
//            }
//            num = numInp;
//            denom = denomInp;
//            redusing();
//        }
//        else {
//            istrm.setstate(std::ios_base::failbit);
//        }
//    }
//    return istrm;
//}
