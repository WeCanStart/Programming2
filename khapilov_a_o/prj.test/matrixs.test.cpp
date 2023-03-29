#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <matrixs/matrixs.hpp>
#include <iostream>


TEST_CASE("[matrixs] - MatrixS ctor") {
    MatrixS a(3, 3);
    MatrixS b(3, 3, 0);
    CHECK(a == b);
    CHECK_THROWS(b = MatrixS(1, -1));
}

TEST_CASE("[matrixs] - MatrixS assignment arithmetic ops") {
    MatrixS a(2, 4, 1);
    MatrixS b(2, 4, 2);
    CHECK((a += 1) == b);
    a = MatrixS(2, 4, 1);
    b = MatrixS(2, 4, 0);
    CHECK((a -= 1) == b);
}

TEST_CASE("[matrixs] - MatrixS arithmetic ops") {
    MatrixS a(2, 4, 1);
    a = a + 1;
    MatrixS b(2, 4, 2);
    CHECK(a == b);
    a = a - 2;
    b = MatrixS(2, 4, 0);
    CHECK(a == b);
}

TEST_CASE("[matrixs] - MatrixS bool operators") {
    MatrixS a(2, 4, 1);
    MatrixS b(2, 4, 1);
    CHECK(a == b);
    b = MatrixS(2, 3, 1);
    CHECK(a != b);
    b = MatrixS(2, 4, 2);
    CHECK(a != b);
}

TEST_CASE("[matrixs] - MatrixS custom operators") {
    MatrixS a{ {1, 2}, {3, 4} };
    MatrixS b{ {37, 54}, {81, 118} };
    a = pow(a, 3);
    CHECK(a == b);
    a = { {1, 2}, {3, 4} };
    b = { {7, 10}, {15, 22} };
    a = sqr(a);
    CHECK(a == b);
}

TEST_CASE("[matrixs] - MatrixS size") {
    MatrixS a{ {1, 2}, {3, 4} };
    a.resize(MatrixS::SizeType(2, 1));
    MatrixS b{ {1}, {3} };
    CHECK(a == b);
    auto s = a.ssize();
    CHECK(s == MatrixS::SizeType(2, 1));
    a.resize(MatrixS::SizeType(1, 1));
    b = { {1} };
    CHECK(a == b);
    s = a.ssize();
    CHECK(s == MatrixS::SizeType(1, 1));
    a.resize(MatrixS::SizeType(2, 2));
    b = { {1, 0}, {0, 0} };
    CHECK(a == b);
    s = a.ssize();
    CHECK(s == MatrixS::SizeType(2, 2));
    a.resize(10, 10);
    CHECK(a.at(0, 0) == 1);
}
