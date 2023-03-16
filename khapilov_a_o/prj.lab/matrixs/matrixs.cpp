#include <matrixs/matrixs.hpp>
#include <iostream>

MatrixS::MatrixS() : rows_(0), cols_(0), data_(nullptr) {};

MatrixS::MatrixS(ptrdiff_t rowsInp_, ptrdiff_t colsInp_) : rows_(rowsInp_), cols_(colsInp_) {
    len_ = rows_ + rows_ * cols_;
    data_ = new int[len_];
    for (ptrdiff_t i = 0; i < rows_; ++i) {
        data_[i] = data_ + rows_ *
    }
    for (ptrdiff_t i = rows_; i < len_; ++i) {

    }
};

MatrixS::MatrixS(ptrdiff_t rowsInp_, ptrdiff_t colsInp_, int num) : rows_(rowsInp_), cols_(colsInp_) {

}

MatrixS::MatrixS(MatrixS&)
{
}

MatrixS::~MatrixS()
{
}

MatrixS& MatrixS::operator+=(int)
{
    // TODO: insert return statement here
}

MatrixS& MatrixS::operator-=(int)
{
    // TODO: insert return statement here
}

MatrixS& MatrixS::operator*=(int)
{
    // TODO: insert return statement here
}

MatrixS& MatrixS::operator/=(int)
{
    // TODO: insert return statement here
}

MatrixS& MatrixS::operator+=(MatrixS)
{
    // TODO: insert return statement here
}

MatrixS& MatrixS::operator-=(MatrixS)
{
    // TODO: insert return statement here
}

MatrixS& MatrixS::operator*=(MatrixS)
{
    // TODO: insert return statement here
}

MatrixS& MatrixS::operator/=(MatrixS)
{
    // TODO: insert return statement here
}

int MatrixS::det()
{
    return 0;
}

MatrixS MatrixS::pow(int)
{
    return MatrixS();
}

MatrixS operator-(MatrixS)
{
    return MatrixS();
}

MatrixS operator+(MatrixS)
{
    return MatrixS();
}

MatrixS operator+(MatrixS, int)
{
    return MatrixS();
}

MatrixS operator-(MatrixS, int)
{
    return MatrixS();
}

MatrixS operator*(MatrixS, int)
{
    return MatrixS();
}

MatrixS operator/(MatrixS, int)
{
    return MatrixS();
}

MatrixS operator+(MatrixS, MatrixS)
{
    return MatrixS();
}

MatrixS operator-(MatrixS, MatrixS)
{
    return MatrixS();
}

MatrixS operator*(MatrixS, MatrixS)
{
    return MatrixS();
}

MatrixS operator/(MatrixS, MatrixS)
{
    return MatrixS();
}
