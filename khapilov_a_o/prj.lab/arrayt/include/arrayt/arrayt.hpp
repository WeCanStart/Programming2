#pragma once
#ifndef ARRAYT_ARRAYT_HPP_20230322
#define ARRAYT_ARRAYT_HPP_20230322

#include <iostream>
#include <string>
#include <sstream>
#include <cstdint>
#include <initializer_list>

template<typename T>
class ArrayT{
public:
    ArrayT();
    explicit ArrayT(const std::ptrdiff_t len);
    ArrayT(const ArrayT<T>&);
    ArrayT(const ArrayT<T>&&) noexcept;
    ArrayT(std::ptrdiff_t sizeInp, T number);
    ArrayT(std::initializer_list<T> initList);   //not explicit

    ~ArrayT();

    std::ptrdiff_t ssize() const;

    T& operator[](std::ptrdiff_t index);
    const T& operator[](std::ptrdiff_t index) const;

    void reserve(std::ptrdiff_t newCapacity_);
    void resize(std::ptrdiff_t newSsize_);

    void insert(std::ptrdiff_t, T num);
    void remove(std::ptrdiff_t);

    void push_back(T newElement);
    T pop_back();

    ArrayT<T>& operator=(const ArrayT<T>& rhs);
    ArrayT<T>& operator+=(const T rhs);
    ArrayT<T>& operator-=(const T rhs);
    ArrayT<T>& operator*=(const T rhs);
    ArrayT<T>& operator/=(const T rhs);

    ArrayT<T>& operator+();
    ArrayT<T>& operator-();

    std::ostream& writeTo(std::ostream& ostrm) const;
    /*std::istream& readFrom(std::istream& istrm);*/

public:
    std::ptrdiff_t ssize_;
    std::ptrdiff_t capacity_;
    T* memory_;

    static const char cmm{ ',' };
};

template<typename T>
ArrayT<T>::ArrayT<T>() {
    memory_ = nullptr;
    ssize_ = 0;
    capacity_ = 0;
}
template<typename T>
ArrayT<T>::ArrayT<T>(const ArrayT<T>& prev) : ssize_(prev.ssize_), capacity_(prev.capacity_), memory_(nullptr) {
    if (this == &prev) {
        return;
    }
    memory_ = new T[capacity_];
    if (prev.memory_ == nullptr) {
        memory_ = nullptr;
    }
    else {
        std::copy(prev.memory_, prev.memory_ + prev.ssize_, memory_);
    }
}
template<typename T>
ArrayT<T>::ArrayT<T>(const ArrayT<T>&& prev) noexcept : ssize_(prev.ssize_), capacity_(prev.capacity_), memory_(nullptr) {
    if (this == &prev) {
        return;
    }
    memory_ = new T[capacity_];
    if (prev.memory_ == nullptr) {
        memory_ = nullptr;
    }
    else {
        std::copy(prev.memory_, prev.memory_ + prev.ssize_, memory_);
    }
}
template<typename T>
ArrayT<T>::ArrayT<T>(std::ptrdiff_t sizeInp) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    ssize_ = sizeInp;
    capacity_ = sizeInp;
    memory_ = new T[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        memory_[i] = 0;
    }
}
template<typename T>
ArrayT<T>::ArrayT(std::ptrdiff_t sizeInp, T num) {
    if (sizeInp < 0) {
        throw std::out_of_range("Index out of range");
    }
    ssize_ = sizeInp;
    capacity_ = sizeInp;
    memory_ = new T[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        memory_[i] = num;
    }
}
template<typename T>
ArrayT<T>::ArrayT<T>(std::initializer_list<T> initList) : ssize_(initList.size()), capacity_(initList.size()), memory_(nullptr)
{
    memory_ = new T[ssize_];
    std::copy(initList.begin(), initList.end(), memory_);
}
template<typename T>
ArrayT<T>::~ArrayT<T>()
{
    delete[] memory_;
}

template<typename T>
std::ptrdiff_t ArrayT<T>::ssize() const
{
    return ssize_;
}

template<typename T>
T& ArrayT<T>::operator[](std::ptrdiff_t index) {
    if (index < 0 || index >= ssize()) {
        throw std::out_of_range("Index out of range");
    }
    return memory_[index];
}

template<typename T>
const T& ArrayT<T>::operator[](std::ptrdiff_t index) const {
    if (index < 0 || index >= ssize()) {
        throw std::out_of_range("Index out of range");
    }
    return memory_[index];
}

template<typename T>
void ArrayT<T>::reserve(std::ptrdiff_t newCapacity_) {
    capacity_ = newCapacity_;
    if (capacity_ < ssize()) {
        ssize_ = capacity_;
        return;
    }
    T* newMemory_ = new T[capacity_];
    if (memory_ == nullptr) {
        memory_ = nullptr;
    }
    else {
        std::copy(memory_, memory_ + ssize(), newMemory_);
    }
    for (std::ptrdiff_t i = ssize(); i < capacity_; ++i) {
        newMemory_[i] = 0;
    }
    delete[] memory_;
    memory_ = newMemory_;
}

template<typename T>
void ArrayT<T>::resize(std::ptrdiff_t newSsize_) {
    if (newSsize_ > capacity_) {
        reserve(newSsize_);
    }
    if (newSsize_ > ssize()) {
        for (std::ptrdiff_t i = ssize(); i < newSsize_; ++i) {
            memory_[i] = 0;
        }
    }
    ssize_ = newSsize_;
}

template<typename T>
void ArrayT<T>::insert(std::ptrdiff_t pos, T num)
{
    if (pos < 0 || pos > ssize()) {
        throw std::out_of_range("Wrong position");
    }
    resize(ssize() + 1);
    for (std::ptrdiff_t i = ssize() - 1; i > pos; --i) {
        memory_[i] = memory_[i - 1];
    }
    memory_[pos] = num;
}

template<typename T>
void ArrayT<T>::remove(std::ptrdiff_t pos)
{
    if (pos < 0 || pos > ssize()) {
        throw std::out_of_range("Wrong position");
    }
    for (std::ptrdiff_t i = pos + 1; i < ssize(); ++i) {
        memory_[i - 1] = memory_[i];
    }
    resize(ssize() - 1);
}

template<typename T>
void ArrayT<T>::push_back(T newElement) {
    if (ssize() == capacity_) {
        resize(static_cast<std::ptrdiff_t>(ssize() + 1));
    }
    memory_[ssize_ - 1] = newElement;
}

template<typename T>
T ArrayT<T>::pop_back() {
    T tmp = memory_[ssize() - 1];
    resize(ssize() - 1);
    return tmp;
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& rhs) {
    if (this == &rhs) {
        return *this;
    }
    ssize_ = rhs.ssize_;
    capacity_ = rhs.capacity_;
    delete[] memory_;
    memory_ = new T[capacity_];
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        new (memory_ + i) T(rhs.memory_[i]);
    }
    return *this;
}
template<typename T>
ArrayT<T>& ArrayT<T>::operator+=(const T rhs) {
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        memory_[i] += rhs;
    }
    return *this;
}
template<typename T>
ArrayT<T>& ArrayT<T>::operator-=(const T rhs) {
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        memory_[i] -= rhs;
    }
    return *this;
}
template<typename T>
ArrayT<T>& ArrayT<T>::operator*=(const T rhs) {
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        memory_[i] *= rhs;
    }
    return *this;
}
template<typename T>
ArrayT<T>& ArrayT<T>::operator/=(const T rhs) {
    if (rhs == 0) {
        throw std::invalid_argument("Divide by zero exception");
    }
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        memory_[i] /= rhs;
    }
    return *this;
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator+() {
    return *this;
}
template<typename T>
ArrayT<T>& ArrayT<T>::operator-() {
    for (std::ptrdiff_t i = 0; i < ssize(); ++i) {
        memory_[i] = -memory_[i];
    }
    return *this;
}

template<typename T>
std::ostream& operator<<(std::ostream& ostrm, const ArrayT<T>& rhs) {
    return rhs.writeTo(ostrm);
}
//std::istream& operator>>(std::istream& istrm, ArrayT<T>& rhs) {
//    return rhs.readFrom(istrm);
//}

template<typename T>
ArrayT<T> operator+(ArrayT<T> lhs, const T rhs) {
    lhs += rhs;
    return lhs;
}
template<typename T>
ArrayT<T> operator-(ArrayT<T> lhs, const T rhs) {
    lhs -= rhs;
    return lhs;
}
template<typename T>
ArrayT<T> operator*(ArrayT<T> lhs, const T rhs) {
    lhs *= rhs;
    return lhs;
}
template<typename T>
ArrayT<T> operator/(ArrayT<T> lhs, const T rhs) {
    lhs /= rhs;
    return lhs;
}

template<typename T>
bool operator==(const ArrayT<T>& lhs, const ArrayT<T>& rhs) {
    if (lhs.ssize_ != rhs.ssize_) {
        return false;
    }
    bool isEqual = true;
    for (std::ptrdiff_t i = 0; i < lhs.ssize_; ++i) {
        isEqual &= (std::abs(lhs[i] - rhs[i]) < FLT_EPSILON);
    }
    return isEqual;
}

template<typename T>
bool operator!=(const ArrayT<T>& lhs, const ArrayT<T>& rhs) {
    return !(lhs == rhs);
}

template<typename T>
std::ostream& ArrayT<T>::writeTo(std::ostream& ostrm) const
{
    ostrm << '[';
    for (std::ptrdiff_t i = 0; i < ssize() - 1; ++i) {
        ostrm << memory_[i] << cmm;
    }
    ostrm << memory_[ssize_ - 1] << ']';
    return ostrm;
}

//std::istream& ArrayT<T>::readFrom(std::istream& istrm)
//{
//    T numInp(0);
//    char sym(0);
//    istrm >> sym;
//    std::istringstream input;
//    for (int i = 0; i < ssize(); ++i) {
//        istrm >> sym >> input;
//    }
//    
//    if (istrm.good()) {
//        if (ArrayT<T>::cmm == sym) {
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

//std::istream& operator>>(std::istream& istrm, ArrayT<T>& rhs);

#endif
