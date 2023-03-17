#include <matrixs/matrixs.hpp>
#include <iostream>

MatrixS::MatrixS() : rows_(0), cols_(0), len_(0), data_(nullptr) {};

MatrixS::MatrixS(ptrdiff_t rowsInp_, ptrdiff_t colsInp_) : rows_(rowsInp_), cols_(colsInp_) {
    if (rows_ < 0 || cols_ < 0) {
        throw std::invalid_argument("sizes must be positive");
    }
    len_ = rows_ + rows_ * cols_;
    data_ = new int[len_];
    for (ptrdiff_t i = 0; i < rows_; ++i) {
        data_[i] = rows_ + i * cols_;
    }
    for (ptrdiff_t i = rows_; i < len_; ++i) {
        data_[i] = 0;
    }
}

MatrixS::MatrixS(ptrdiff_t rowsInp_, ptrdiff_t colsInp_, int num) : rows_(rowsInp_), cols_(colsInp_) {
    if (rows_ < 0 || cols_ < 0) {
        throw std::invalid_argument("sizes must be positive");
    }
    len_ = rows_ + rows_ * cols_;
    data_ = new int[len_];
    for (ptrdiff_t i = 0; i < rows_; ++i) {
        data_[i] = rows_ + i * cols_;
    }
    for (ptrdiff_t i = rows_; i < len_; ++i) {
        data_[i] = num;
    }
}

MatrixS::MatrixS(MatrixS& prev) : rows_(prev.rows_), cols_(prev.cols_), len_(prev.len_), data_(nullptr){
    if (this == &prev) {
        return;
    }
    rows_ = prev.rows_;
    cols_ = prev.cols_;
    len_ = prev.len_;
    data_ = new int[len_];
    std::copy(prev.data_, prev.data_ + len_, data_);
}

MatrixS::MatrixS(MatrixS&& prev) noexcept : rows_(prev.rows_), cols_(prev.cols_), len_(prev.len_), data_(nullptr){
    if (this == &prev) {
        return;
    }
    rows_ = prev.rows_;
    cols_ = prev.cols_;
    len_ = prev.len_;
    data_ = new int[len_];
    std::copy(prev.data_, prev.data_ + len_, data_);
}

MatrixS::~MatrixS()
{
    delete[] data_;
}

const int& MatrixS::at(int row_, int col_) const{
    if (row_ >= rows_ || data_[row_] + col_ >= len_) {
        throw std::out_of_range("Wrong position");
    }
    return data_[data_[row_] + col_];
}
int& MatrixS::at(int row_, int col_) {
    if (row_ >= rows_ || data_[row_] + col_ >= len_) {
        throw std::out_of_range("Wrong position");
    }
    return data_[data_[row_] + col_];
}

int MatrixS::getNumRows() const
{
    return rows_;
}
int MatrixS::getNumCols() const
{
    return cols_;
}

MatrixS& MatrixS::operator=(MatrixS& rhs)
{
    if (this == &rhs) {
        return *this;
    }
    rows_ = rhs.rows_;
    cols_ = rhs.cols_;
    len_ = rhs.len_;
    if (data_ != nullptr) {
        delete[] data_;
    }
    data_ = new int[len_];
    for (ptrdiff_t i = 0; i < len_; ++i) {
        data_[i] = rhs.data_[i];
    }
    return *this;
}

MatrixS& MatrixS::operator=(MatrixS&& rhs) noexcept
{
    if (this == &rhs) {
        return *this;
    }
    rows_ = rhs.rows_;
    cols_ = rhs.cols_;
    len_ = rhs.len_;
    if (data_ != nullptr) {
        delete[] data_;
    }
    data_ = new int[len_];
    for (ptrdiff_t i = 0; i < len_; ++i) {
        data_[i] = rhs.data_[i];
    }
    return *this;
}

MatrixS operator+(MatrixS matrix)
{
    return matrix;
}

MatrixS operator-(MatrixS matrix)
{
    for (int i = 0; i < matrix.getNumRows(); ++i) {
        for (int j = 0; j < matrix.getNumCols(); ++j) {
            matrix.at(i, j) = -matrix.at(i, j);
        }
    }
    return matrix;
}

MatrixS& MatrixS::operator+=(int rhs)
{
    for (ptrdiff_t i = rows_; i < len_; ++i) {
        data_[i] += rhs;
    }
    return *this;
}

MatrixS& MatrixS::operator-=(int rhs)
{
    for (ptrdiff_t i = rows_; i < len_; ++i) {
        data_[i] -= rhs;
    }
    return *this;
}

MatrixS& MatrixS::operator*=(int rhs)
{
    for (ptrdiff_t i = rows_; i < len_; ++i) {
        data_[i] *= rhs;
    }
    return *this;
}

MatrixS operator+(MatrixS lhs, int rhs)
{
    lhs += rhs;
    return lhs;
}

MatrixS operator-(MatrixS lhs, int rhs)
{
    lhs -= rhs;
    return lhs;
}

MatrixS operator*(MatrixS lhs, int rhs)
{
    lhs *= rhs;
    return lhs;
}

MatrixS& operator+=(MatrixS& lhs, MatrixS& rhs)
{
    if (lhs.getNumRows() != rhs.getNumRows() || lhs.getNumCols() != rhs.getNumCols()) {
        throw std::invalid_argument("Wrong shape");
    }
    for (ptrdiff_t i = 0; i < lhs.getNumRows(); ++i) {
        for (ptrdiff_t j = 0; j < lhs.getNumCols(); ++j) {
            lhs.at(i, j) += rhs.at(i, j);
        }
    }
    return lhs;
}

MatrixS& operator-=(MatrixS& lhs, MatrixS& rhs)
{
    if (lhs.getNumRows() != rhs.getNumRows() || lhs.getNumCols() != rhs.getNumCols()) {
        throw std::invalid_argument("Wrong shape");
    }
    for (ptrdiff_t i = 0; i < lhs.getNumRows(); ++i) {
        for (ptrdiff_t j = 0; j < lhs.getNumCols(); ++j) {
            lhs.at(i, j) -= rhs.at(i, j);
        }
    }
    return lhs;
}

MatrixS& operator*=(MatrixS& lhs, MatrixS& rhs)
{
    lhs = lhs * rhs;
    return lhs;
}

MatrixS operator+(MatrixS lhs, MatrixS& rhs)
{
    lhs += rhs;
    return lhs;
}

MatrixS operator-(MatrixS lhs, MatrixS& rhs)
{
    lhs -= rhs;
    return lhs;
}

MatrixS operator*(MatrixS& lhs, MatrixS& rhs)
{
    MatrixS ret(lhs.getNumRows(), rhs.getNumCols());
    if (lhs.getNumCols() != rhs.getNumRows()) {
        throw std::invalid_argument("Wrong shape");
    }
    for (ptrdiff_t i = 0; i < lhs.getNumRows(); ++i) {
        for (ptrdiff_t j = 0; j < lhs.getNumCols(); ++j) {
            for (ptrdiff_t k = 0; k < rhs.getNumCols(); ++k)
            ret.at(i, k) += lhs.at(i, j) * rhs.at(j, k);
        }
    }
    return ret;
}

MatrixS sqr(MatrixS& matrix) {
    return matrix * matrix;
}

MatrixS pow(MatrixS matrix, int power)
{
    if (matrix.getNumRows() != matrix.getNumCols()) {
        throw std::invalid_argument("Wrong shape");
    }
    MatrixS answer;
    answer = IdentityMatrix(matrix.getNumRows());
    while (power) {
        if (power & 1) {
            answer *= matrix;
        }
        matrix = sqr(matrix);
        power >>= 1;
    }
    return answer;
}

MatrixS IdentityMatrix(int n)
{
    MatrixS ident(n, n);
    for (int i = 0; i < n; ++i) {
        ident.at(i, i) = 1;
    }
    return ident;
}

bool operator==(MatrixS& lhs, MatrixS& rhs) {
    if (lhs.getNumRows() != rhs.getNumRows() || lhs.getNumCols() != rhs.getNumCols()) {
        return false;
    }
    bool equal = true;
    for (int i = 0; i < lhs.getNumRows(); ++i) {
        for (int j = 0; j < lhs.getNumCols(); ++j) {
            equal &= (lhs.at(i, j) == rhs.at(i, j));
        }
    }
    return equal;
}