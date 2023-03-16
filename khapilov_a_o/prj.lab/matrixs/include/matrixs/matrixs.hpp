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

    ~MatrixS();

    MatrixS& operator+=(int);
    MatrixS& operator-=(int);
    MatrixS& operator*=(int);
    MatrixS& operator/=(int);

    MatrixS& operator+=(MatrixS);
    MatrixS& operator-=(MatrixS);
    MatrixS& operator*=(MatrixS);
    MatrixS& operator/=(MatrixS);

    int det();
    MatrixS pow(int);
public:
    ptrdiff_t rows_;
    ptrdiff_t cols_;
    int* data_;
};

MatrixS operator-(MatrixS);
MatrixS operator+(MatrixS);

MatrixS operator+(MatrixS, int);
MatrixS operator-(MatrixS, int);
MatrixS operator*(MatrixS, int);
MatrixS operator/(MatrixS, int);

MatrixS operator+(MatrixS, MatrixS);
MatrixS operator-(MatrixS, MatrixS);
MatrixS operator*(MatrixS, MatrixS);
MatrixS operator/(MatrixS, MatrixS);

#endif