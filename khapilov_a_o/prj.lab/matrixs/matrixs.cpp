#include <matrixs/matrixs.hpp>
#include <iostream>

MatrixS::MatrixS()
{
    rows_ = 0;
    len_ = 0;
    cols_ = 0;
    data_ = nullptr;
}

MatrixS::MatrixS(const SizeType& s) : rows_(std::get<0>(s)), cols_(std::get<1>(s)), data_(nullptr)
{
    if (rows_ <= 0 || cols_ <= 0) {
        throw std::invalid_argument("Sizes must be positive");
    }
    len_ = rows_ + rows_ * cols_;
    data_ = new int[len_];
    for (std::ptrdiff_t i = 0; i < rows_; ++i) {
        data_[i] = rows_ + i * cols_;
    }
    for (std::ptrdiff_t i = rows_; i < len_; ++i) {
        data_[i] = 0;
    }
}

MatrixS::MatrixS(std::ptrdiff_t rowsInp_, std::ptrdiff_t colsInp_) : rows_(rowsInp_), cols_(colsInp_), data_(nullptr){
    if (rows_ <= 0 || cols_ <= 0) {
        throw std::invalid_argument("Sizes must be positive");
    }
    len_ = rows_ + rows_ * cols_;
    data_ = new int[len_];
    for (std::ptrdiff_t i = 0; i < rows_; ++i) {
        data_[i] = rows_ + i * cols_;
    }
    for (std::ptrdiff_t i = rows_; i < len_; ++i) {
        data_[i] = 0;
    }
}

MatrixS::MatrixS(std::ptrdiff_t rowsInp_, std::ptrdiff_t colsInp_, int num) : rows_(rowsInp_), cols_(colsInp_), len_(rowsInp_ + rowsInp_ * colsInp_), data_(nullptr){
    if (rows_ <= 0 || cols_ <= 0) {
        throw std::invalid_argument("Sizes must be positive");
    }
    //len_ = rows_ + rows_ * cols_;
    data_ = new int[len_];
    for (std::ptrdiff_t i = 0; i < rows_; ++i) {
        data_[i] = rows_ + i * cols_;
    }
    for (std::ptrdiff_t i = rows_; i < len_; ++i) {
        data_[i] = num;
    }
}

MatrixS::MatrixS(std::initializer_list<std::initializer_list<int>> initList)
{
    std::ptrdiff_t rowsNew_ = initList.size();
    if (rowsNew_ == 0) {
        throw std::invalid_argument("Number of rows cannot be 0");
    }
    rows_ = rowsNew_;
    std::ptrdiff_t colsNew_ = initList.begin()->size();
    if (colsNew_ == 0) {
        throw std::invalid_argument("Number of columns cannot be 0");
    }
    cols_ = colsNew_;
    len_ = rows_ + rows_ * cols_;
    data_ = new int[len_];
    std::ptrdiff_t i = 0;
    for (std::ptrdiff_t i = 0; i < rows_; ++i) {
        data_[i] = rows_ + i * cols_;
    }
    for (auto subList: initList) {
        if (colsNew_ != subList.size()) {
            throw std::invalid_argument("Rows must have the same size");
        }
        std::copy(subList.begin(), subList.end(), data_ + rows_ + cols_ * i);
        ++i;
    }
}

MatrixS::MatrixS(const MatrixS& prev) : rows_(prev.rows_), cols_(prev.cols_), len_(prev.len_), data_(nullptr){
    if (this == &prev) {
        return;
    }
    data_ = new int[len_];
    std::copy(prev.data_, prev.data_ + len_, data_);
}

//MatrixS::MatrixS(MatrixS&& prev) noexcept : rows_(prev.rows_), cols_(prev.cols_), len_(prev.len_), data_(nullptr){
//    if (this == &prev) {
//        return;
//    }
//    data_ = new int[len_];
//    std::copy(prev.data_, prev.data_ + len_, data_);
//} 

MatrixS::~MatrixS()
{
    delete[] data_;
}

const int& MatrixS::at(const std::ptrdiff_t row, const std::ptrdiff_t col) const {
    if (row >= rows_ || data_[row] + col >= len_ || row < 0 || data_[row] + col < 0) {
        throw std::out_of_range("Wrong position");
    }
    return data_[data_[row] + col];
}
int& MatrixS::at(const std::ptrdiff_t row, const std::ptrdiff_t col) {
    if (row >= rows_ || data_[row] + col >= len_ || row < 0 || data_[row] + col < 0) {
        throw std::out_of_range("Wrong position");
    }
    return data_[data_[row] + col];
}
const int& MatrixS::at(const MatrixS::SizeType s) const{
    if (std::get<0>(s) >= rows_ || data_[std::get<0>(s)] + std::get<1>(s) >= len_ || std::get<0>(s) < 0 || data_[std::get<0>(s)] + std::get<1>(s) < 0) {
        throw std::out_of_range("Wrong position");
    }
    return data_[data_[std::get<0>(s)] + std::get<1>(s)];
}
int& MatrixS::at(const MatrixS::SizeType s) {
    if (std::get<0>(s) >= rows_ || data_[std::get<0>(s)] + std::get<1>(s) >= len_ || std::get<0>(s) < 0 || data_[std::get<0>(s)] + std::get<1>(s) < 0) {
        throw std::out_of_range("Wrong position");
    }
    return data_[data_[std::get<0>(s)] + std::get<1>(s)];
}

std::ptrdiff_t MatrixS::nRows() const noexcept
{
    return rows_;
}
std::ptrdiff_t MatrixS::nCols() const noexcept
{
    return cols_;
}

void MatrixS::resize(const std::ptrdiff_t row, const std::ptrdiff_t col)
{
    if (row <= 0 || col <= 0) {
        throw std::invalid_argument("Sizes must be positive");
    }
    MatrixS newMatrix(row, col);
    for (std::ptrdiff_t r = 0; r < row; ++r) {
        for (std::ptrdiff_t c = 0; c < col; ++c) {
            if (rows_ <= r || cols_ <= c) {
                newMatrix.at(SizeType(r, c)) = 0;
            }
            else {
                newMatrix.at(SizeType(r, c)) = at(SizeType(r, c));
            }
        }
    }
    *this = newMatrix;
}
void MatrixS::resize(const SizeType& s)
{
    if (std::get<0>(s) <= 0 || std::get<1>(s) <= 0) {
        throw std::invalid_argument("Sizes must be positive");
    }
    MatrixS newMatrix(std::get<0>(s), std::get<1>(s));
    for (std::ptrdiff_t r = 0; r < std::get<0>(s); ++r) {
        for (std::ptrdiff_t c = 0; c < std::get<1>(s); ++c) {
            if (rows_ <= r || cols_ <= c) {
                newMatrix.at(SizeType(r, c)) = 0;
            }
            else {
                newMatrix.at(SizeType(r, c)) = at(SizeType(r, c));
            }
        }
    }
    *this = newMatrix;
}

MatrixS::SizeType MatrixS::ssize() const noexcept
{
    return SizeType(rows_, cols_);
}

MatrixS& MatrixS::operator=(const MatrixS& rhs)
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
    for (std::ptrdiff_t i = 0; i < len_; ++i) {
        data_[i] = rhs.data_[i];
    }
    return *this;
}

//MatrixS& MatrixS::operator=(MatrixS&& rhs) noexcept
//{
//    if (this == &rhs) {
//        return *this;
//    }
//    rows_ = rhs.rows_;
//    cols_ = rhs.cols_;
//    len_ = rhs.len_;
//    if (data_ != nullptr) {
//        delete[] data_;
//    }
//    data_ = new int[len_];
//    for (std::ptrdiff_t i = 0; i < len_; ++i) {
//        data_[i] = rhs.data_[i];
//    }
//    return *this;
//}

MatrixS operator+(MatrixS matrix)
{
    return matrix;
}

MatrixS operator-(MatrixS matrix)
{
    for (int i = 0; i < matrix.nRows(); ++i) {
        for (int j = 0; j < matrix.nCols(); ++j) {
            matrix.at(MatrixS::SizeType(i, j)) = -matrix.at(MatrixS::SizeType(i, j));
        }
    }
    return matrix;
}

MatrixS& MatrixS::operator+=(int rhs)
{
    for (std::ptrdiff_t i = rows_; i < len_; ++i) {
        data_[i] += rhs;
    }
    return *this;
}

MatrixS& MatrixS::operator-=(int rhs)
{
    for (std::ptrdiff_t i = rows_; i < len_; ++i) {
        data_[i] -= rhs;
    }
    return *this;
}

MatrixS& MatrixS::operator*=(int rhs)
{
    for (std::ptrdiff_t i = rows_; i < len_; ++i) {
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
    if (lhs.nRows() != rhs.nRows() || lhs.nCols() != rhs.nCols()) {
        throw std::invalid_argument("Wrong shape");
    }
    for (std::ptrdiff_t i = 0; i < lhs.nRows(); ++i) {
        for (std::ptrdiff_t j = 0; j < lhs.nCols(); ++j) {
            lhs.at(MatrixS::SizeType(i, j)) += rhs.at(MatrixS::SizeType(i, j));
        }
    }
    return lhs;
}

MatrixS& operator-=(MatrixS& lhs, MatrixS& rhs)
{
    if (lhs.nRows() != rhs.nRows() || lhs.nCols() != rhs.nCols()) {
        throw std::invalid_argument("Wrong shape");
    }
    for (std::ptrdiff_t i = 0; i < lhs.nRows(); ++i) {
        for (std::ptrdiff_t j = 0; j < lhs.nCols(); ++j) {
            lhs.at(MatrixS::SizeType(i, j)) -= rhs.at(MatrixS::SizeType(i, j));
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
    MatrixS ret(lhs.nRows(), rhs.nCols());
    if (lhs.nCols() != rhs.nRows()) {
        throw std::invalid_argument("Wrong shape");
    }
    for (std::ptrdiff_t i = 0; i < lhs.nRows(); ++i) {
        for (std::ptrdiff_t j = 0; j < lhs.nCols(); ++j) {
            for (std::ptrdiff_t k = 0; k < rhs.nCols(); ++k) {
                ret.at(MatrixS::SizeType(i, k)) += lhs.at(MatrixS::SizeType(i, j)) * rhs.at(MatrixS::SizeType(j, k));
            }
        }
    }
    return ret;
}

MatrixS sqr(MatrixS& matrix) {
    return matrix * matrix;
}

MatrixS pow(MatrixS matrix, int power)
{
    if (matrix.nRows() != matrix.nCols()) {
        throw std::invalid_argument("Wrong shape");
    }
    int r = matrix.nRows();
    MatrixS ident = identityMatrix(r);
    MatrixS answer(ident);
    while (power) {
        if (power & 1) {
            answer *= matrix;
        }
        matrix = sqr(matrix);
        power >>= 1;
    }
    return answer;
}

MatrixS identityMatrix(int n)
{
    MatrixS ident = MatrixS(n, n);
    for (int i = 0; i < n; ++i) {
        ident.at(MatrixS::SizeType(i, i)) = 1;
    }
    return ident;
}

bool operator==(MatrixS& lhs, MatrixS& rhs) {
    if (lhs.nRows() != rhs.nRows() || lhs.nCols() != rhs.nCols()) {
        return false;
    }
    bool equal = true;
    for (int i = 0; i < lhs.nRows(); ++i) {
        for (int j = 0; j < lhs.nCols(); ++j) {
            equal &= (lhs.at(MatrixS::SizeType(i, j)) == rhs.at(MatrixS::SizeType(i, j)));
        }
    }
    return equal;
}