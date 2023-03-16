#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <arrayd/arrayd.hpp>
#include <iostream>


TEST_CASE("[arrayd] - ArrayD ctor") {
    ArrayD a(3);
    ArrayD b(3, 0);
    CHECK(a == b);
    a = ArrayD();
    b = ArrayD(0);
    CHECK(a == b);
    CHECK_THROWS(ArrayD(-3));
}

TEST_CASE("[arrayd] - ArrayD assignment arithmetic ops") {
    ArrayD a(2, 4);
    ArrayD b(2, 5);
    CHECK((a += 1) == b);
    CHECK(a == b);
    a = ArrayD(2, 4);
    b = ArrayD(2, 3);
    CHECK((a -= 1) == b);
    CHECK(a == b);
    a = ArrayD(2, 4);
    b = ArrayD(2, 8);
    CHECK((a *= 2) == b);
    CHECK(a == b);
    a = ArrayD(2, 4);
    b = ArrayD(2, 2);
    CHECK((a /= 2) == b);
    CHECK(a == b);
    a = ArrayD(2, 4);
    b = ArrayD(0);
    CHECK((b = a) == a);
    CHECK_THROWS(a /= 0);
}

TEST_CASE("[arrayd] - ArrayD arithmetic ops") {
    ArrayD a(2, 4);
    ArrayD b(2, 5);
    a = a + 1;
    CHECK(a == b);
    b = ArrayD(2, 4);
    a = a - 1;
    CHECK(a == b);
    b = ArrayD(2, 8);
    a = a * 2;
    CHECK(a == b);
    b = ArrayD(2, 2);
    a = a / 4;
    CHECK(a == b);
    CHECK_THROWS(a / 0);
}

TEST_CASE("[arrayd] - ArrayD bool operators") {
    ArrayD a(2, 4);
    ArrayD b(2, 4);
    CHECK(a == b);
    b = ArrayD(2, 3);
    CHECK(a != b);
    b = ArrayD(1, 4);
    CHECK(a != b);
}
