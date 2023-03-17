#include <arrayd/arrayd.hpp>
#include <iostream>
#include <string>
#include <sstream>

ArrayD::ArrayD() {
    memory_ = nullptr;
    ssize_ = 0;
    capacity_ = 0;
}
ArrayD::ArrayD(const ArrayD& prev) {
    ssize_ = prev.ssize_;
    capacity_ = prev.capacity_;
    memory_ = new double[capacity_];
    if (prev.memory_ == nullptr) {
        memory_ = nullptr;
    }
    else {
        std::copy(prev.memory_, prev.memory_ + prev.ssize_, memory_);
    }
}
ArrayD::ArrayD(const ArrayD&& prev) noexcept : ssize_(prev.ssize_), capacity_(prev.capacity_){
    memory_ = new double[capacity_];
    if (prev.memory_ == nullptr) {
        memory_ = nullptr;
    }
    else {
        std::copy(prev.memory_, prev.memory_ + prev.ssize_, memory_);
    }
}
ArrayD::ArrayD(std::ptrdiff_t sizeInp) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    ssize_ = sizeInp;
    capacity_ = sizeInp;
    memory_ = new double[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] = 0;
    }
}
ArrayD::ArrayD(std::ptrdiff_t sizeInp, double num) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    ssize_ = sizeInp;
    capacity_ = sizeInp;
    memory_ = new double[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] = num;
    }
}

ArrayD::~ArrayD()
{
    delete[] memory_;
}

double& ArrayD::operator[](std::ptrdiff_t index) {
    if (index < 0 || index >= ssize_) {
        throw std::out_of_range("Index out of range");
    }
    return memory_[index];
}

const double& ArrayD::operator[](std::ptrdiff_t index) const{
    if (index < 0 || index >= ssize_) {
        throw std::out_of_range("Index out of range");
    }
    return memory_[index];
}

void ArrayD::reserve(std::ptrdiff_t newCapacity_) {
    capacity_ = newCapacity_;
    if (capacity_ < ssize_) {
        ssize_ = capacity_;
        return;
    }
    double* newMemory_ = new double[capacity_];
    if (memory_ == nullptr) {
        memory_ = nullptr;
    }
    else {
        std::copy(memory_, memory_ + ssize_, newMemory_);
    }
    for (std::ptrdiff_t i = ssize_; i < capacity_; ++i) {
        newMemory_[i] = 0;
    }
    delete[] memory_;
    memory_ = newMemory_;
}

void ArrayD::resize(std::ptrdiff_t newSsize_) {
    if (newSsize_ > capacity_) {
        reserve(newSsize_);
    }
    ssize_ = newSsize_;
}

void ArrayD::push_back(double newElement) {
    if (ssize_ == capacity_) {
        resize(static_cast<std::ptrdiff_t>(ssize_ + 1));
    }
    memory_[ssize_ - 1] = newElement;
}

double ArrayD::pop_back() {
    double tmp = memory_[ssize_ - 1];
    resize(ssize_ - 1);
    return tmp;
}

ArrayD& ArrayD::operator=(const ArrayD& rhs) {
    ssize_ = rhs.ssize_;
    capacity_ = rhs.capacity_;
    delete[] memory_;
    memory_ = new double[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize_; ++i) {
        new (memory_ + i) double (rhs.memory_[i]);
    }
    return *this;
}
ArrayD& ArrayD::operator+=(const double rhs) {
    for (std::ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] += rhs;
    }
    return *this;
}
ArrayD& ArrayD::operator-=(const double rhs) {
    for (std::ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] -= rhs;
    }
    return *this;
}
ArrayD& ArrayD::operator*=(const double rhs) {
    for (std::ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] *= rhs;
    }
    return *this;
}
ArrayD& ArrayD::operator/=(const double rhs) {
    if (rhs == 0) {
        throw std::invalid_argument("Divide by zero exception");
    }
    for (std::ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] /= rhs;
    }
    return *this;
}

ArrayD& ArrayD::operator+() {
    return *this;
}
ArrayD& ArrayD::operator-() {
    for (std::ptrdiff_t i = 0; i < ssize_; ++i) {
        memory_[i] = -memory_[i];
    }
    return *this;
}

std::ostream& operator<<(std::ostream& ostrm, const ArrayD& rhs) {
    return rhs.writeTo(ostrm);
}
//std::istream& operator>>(std::istream& istrm, ArrayD& rhs) {
//    return rhs.readFrom(istrm);
//}

ArrayD operator+(ArrayD lhs, const double rhs) {
    lhs += rhs;
    return lhs;
}
ArrayD operator-(ArrayD lhs, const double rhs) {
    lhs -= rhs;
    return lhs;
}
ArrayD operator*(ArrayD lhs, const double rhs) {
    lhs *= rhs;
    return lhs;
}
ArrayD operator/(ArrayD lhs, const double rhs) {
    lhs /= rhs;
    return lhs;
}

bool operator==(const ArrayD& lhs, const ArrayD& rhs) {
    if (lhs.ssize_ != rhs.ssize_) {
        return false;
    }
    bool isEqual = true;
    for (std::ptrdiff_t i = 0; i < lhs.ssize_; ++i) {
        isEqual &= (std::abs(lhs[i] - rhs[i]) < FLT_EPSILON);
    }
    return isEqual;
}

bool operator!=(const ArrayD& lhs, const ArrayD& rhs) {
    return !(lhs == rhs);
}

std::ostream& ArrayD::writeTo(std::ostream& ostrm) const
{
    ostrm << '[';
    for (std::ptrdiff_t i = 0; i < ssize_ - 1; ++i) {
        ostrm << memory_[i] << cmm;
    }
    ostrm << memory_[ssize_ - 1] << ']';
    return ostrm;
}

//std::istream& ArrayD::readFrom(std::istream& istrm)
//{
//    double numInp(0);
//    char sym(0);
//    istrm >> sym;
//    std::istringstream input;
//    for (int i = 0; i < ssize_; ++i) {
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
