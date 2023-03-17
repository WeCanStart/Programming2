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
    CHECK_THROWS(a = ArrayD(-3));
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

TEST_CASE("[arrayd] - ArrayD size & capacity") {
    ArrayD a(1, 0);
    CHECK(a[0] == 0);
    a.push_back(1);
    CHECK(a[1] == 1);
    a.insert(2, 2);
    CHECK(a[2] == 2);
    a.insert(1, 3);
    CHECK(a[1] == 3);
    CHECK(a[2] == 1);
    a.pop_back();
    CHECK(a[2] == 1);
    a.remove(0);
    CHECK(a[1] == 1);
}
