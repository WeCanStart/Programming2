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
    MatrixS a(2, 4);
    MatrixS b(2, 4);
    CHECK(a == b);
    b = MatrixS(2, 3);
    CHECK(a != b);
    b = MatrixS(1, 4);
    CHECK(a != b);
}

TEST_CASE("[matrixs] - MatrixS custom operators") {
    MatrixS a(2, 2);
    MatrixS b(2, 2);
    a.at(0, 0) = 1;
    a.at(0, 1) = 2;
    a.at(1, 0) = 3;
    a.at(1, 1) = 4;
    b.at(0, 0) = 37;
    b.at(0, 1) = 54;
    b.at(1, 0) = 81;
    b.at(1, 1) = 118;
    a = pow(a, 3);
    CHECK(a == b);
    a.at(0, 0) = 1;
    a.at(0, 1) = 2;
    a.at(1, 0) = 3;
    a.at(1, 1) = 4;
    b.at(0, 0) = 7;
    b.at(0, 1) = 10;
    b.at(1, 0) = 15;
    b.at(1, 1) = 22;
    a = sqr(a);
    
}