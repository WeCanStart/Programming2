#include <matrixs/matrixs.hpp>
#include <iostream>

MatrixS::MatrixS() : cols_(0), rows_(0), data_(nullptr) {};

MatrixS::MatrixS(ptrdiff_t rowsInp_, ptrdiff_t colsInp_) : cols_()
{
}

MatrixS::MatrixS(ptrdiff_t rowsInp_, ptrdiff_t colsInp_, int num)
{
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
