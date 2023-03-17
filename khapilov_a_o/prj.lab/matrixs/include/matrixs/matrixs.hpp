#pragma once

#ifndef MATRIXS_MATRIXS_HPP_20230315
#define MATRIXS_MATRIXS_HPP_20230315

#include <iosfwd>
#include <cstdint>

class MatrixS {
public:
    MatrixS();
    MatrixS(ptrdiff_t rowsInp_, ptrdiff_t colsInp_);
    MatrixS(ptrdiff_t rowsInp_, ptrdiff_t colsInp_, int num);
    MatrixS(MatrixS&);
    MatrixS(MatrixS&&) noexcept;

    ~MatrixS();

    const int& at(int, int) const;
    int& at(int, int);

    int getNumRows() const;
    int getNumCols() const;

    MatrixS& operator=(MatrixS&);
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
MatrixS IdentityMatrix(int);

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