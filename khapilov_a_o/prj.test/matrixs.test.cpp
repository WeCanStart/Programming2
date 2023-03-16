#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <matrixs/matrixs.hpp>
#include <iostream>


TEST_CASE("[matrixs] - MatrixS ctor") {
    MatrixS a(3, 3);
    MatrixS b(3, 3, 0);
    CHECK(a == b);
    CHECK_THROWS(MatrixS(1, -1));
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
