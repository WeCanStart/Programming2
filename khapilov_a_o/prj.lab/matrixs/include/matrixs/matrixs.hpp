#pragma once

#ifndef MATRIXS_MATRIXS_HPP_20230315
#define MATRIXS_MATRIXS_HPP_20230315

#include <iosfwd>
#include <utility>

class MatrixS {
public:
    using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;
public:
    explicit MatrixS(const SizeType& s = {0, 0});
    MatrixS(ptrdiff_t rowsInp_, ptrdiff_t colsInp_);
    MatrixS(ptrdiff_t rowsInp_, ptrdiff_t colsInp_, int num);
    MatrixS(std::initializer_list<std::initializer_list<int>> initList);
    MatrixS(const MatrixS&);
    //MatrixS(MatrixS&&) noexcept;

    ~MatrixS();

    const int& at(const std::ptrdiff_t, const std::ptrdiff_t) const;
    int& at(const std::ptrdiff_t, const std::ptrdiff_t);
    const int& at(const SizeType) const;
    int& at(const SizeType);

    std::ptrdiff_t nRows() const noexcept;
    std::ptrdiff_t nCols() const noexcept;

    void resize(const std::ptrdiff_t, const std::ptrdiff_t);
    void resize(const SizeType&);

    SizeType ssize() const noexcept;

    MatrixS& operator=(const MatrixS&);
    MatrixS& operator=(MatrixS&&) noexcept;

    MatrixS& operator+=(int);
    MatrixS& operator-=(int);
    MatrixS& operator*=(int);

public:
    ptrdiff_t rows_;
    ptrdiff_t cols_;
    ptrdiff_t len_;
    int* data_;
};
MatrixS identityMatrix(int);

MatrixS operator+(MatrixS);
MatrixS operator-(MatrixS);
MatrixS operator+(MatrixS, int);
MatrixS operator-(MatrixS, int);
MatrixS operator*(MatrixS, int);

MatrixS& operator+=(MatrixS&, MatrixS&);
MatrixS& operator-=(MatrixS&, MatrixS&);
MatrixS& operator*=(MatrixS&, MatrixS&);

MatrixS operator+(MatrixS, MatrixS&);
MatrixS operator-(MatrixS, MatrixS&);
MatrixS operator*(MatrixS&, MatrixS&);

MatrixS sqr(MatrixS&);
MatrixS pow(MatrixS, int);

bool operator==(MatrixS& lhs, MatrixS& rhs);

#endif