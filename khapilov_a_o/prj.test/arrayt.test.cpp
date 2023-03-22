#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.hpp>
#include <arrayt/arrayt.hpp>
#include <iostream>

typedef double T;
TEST_CASE("[arrayd] - ArrayT<T> ctor") {
    ArrayT<T> a(3);
    ArrayT<T> b{0.0, 0.0, 0.0};
    CHECK(a == b);
    a = ArrayT<T>();
    b = ArrayT<T>(0);
    CHECK(a == b);
    CHECK_THROWS(a = ArrayT<T>(-3));
}

TEST_CASE("[arrayd] - ArrayT<T> assignment arithmetic ops") {
    ArrayT<T> a(2, 4.0);
    ArrayT<T> b(2, 5.0);
    CHECK((a += 1.0) == b);
    CHECK(a == b);
    a = ArrayT<T>(2, 4.0);
    b = ArrayT<T>(2, 3.0);
    CHECK((a -= 1.0) == b);
    CHECK(a == b);
    a = ArrayT<T>(2, 4.0);
    b = ArrayT<T>(2, 8.0);
    CHECK((a *= 2.0) == b);
    CHECK(a == b);
    a = ArrayT<T>(2, 4.0);
    b = ArrayT<T>(2, 2.0);
    CHECK((a /= 2.0) == b);
    CHECK(a == b);
    a = ArrayT<T>(2, 4.0);
    b = ArrayT<T>(0.0);
    CHECK((b = a) == a);
    CHECK_THROWS(a /= 0.0);
}

TEST_CASE("[arrayd] - ArrayT<T> arithmetic ops") {
    ArrayT<T> a(2, 4.0);
    ArrayT<T> b(2, 5.0);
    a = a + 1.0;
    CHECK(a == b);
    b = ArrayT<T>(2, 4.0);
    a = a - 1.0;
    CHECK(a == b);
    b = ArrayT<T>(2, 8.0);
    a = a * 2.0;
    CHECK(a == b);
    b = ArrayT<T>(2, 2.0);
    a = a / 4.0;
    CHECK(a == b);
    CHECK_THROWS(a / 0.0);
}

TEST_CASE("[arrayd] - ArrayT<T> bool operators") {
    ArrayT<T> a(2, 4.0);
    ArrayT<T> b(2, 4.0);
    CHECK(a == b);
    b = ArrayT<T>(2, 3.0);
    CHECK(a != b);
    b = ArrayT<T>(1, 4.0);
    CHECK(a != b);
}

TEST_CASE("[arrayd] - ArrayT<T> size & capacity") {
    ArrayT<T> a(1, 0.0);
    CHECK(a[0] == 0.0);
    a.push_back(1);
    CHECK(a[1] == 1.0);
    a.insert(2, 2);
    CHECK(a[2] == 2.0);
    a.insert(1, 3);
    CHECK(a[1] == 3.0);
    CHECK(a[2] == 1.0);
    a.pop_back();
    CHECK(a[2] == 1.0);
    a.remove(0);
    CHECK(a[1] == 1.0);
}

typedef int T1;
TEST_CASE("[arrayd] - ArrayT<T> ctor") {
    ArrayT<T1> a(3);
    ArrayT<T1> b{ 0, 0, 0 };
    CHECK(a == b);
    a = ArrayT<T1>();
    b = ArrayT<T1>(0);
    CHECK(a == b);
    CHECK_THROWS(a = ArrayT<T1>(-3));
}

TEST_CASE("[arrayd] - ArrayT<T> assignment arithmetic ops") {
    ArrayT<T1> a(2, 4);
    ArrayT<T1> b(2, 5);
    CHECK((a += 1) == b);
    CHECK(a == b);
    a = ArrayT<T1>(2, 4);
    b = ArrayT<T1>(2, 3);
    CHECK((a -= 1) == b);
    CHECK(a == b);
    a = ArrayT<T1>(2, 4);
    b = ArrayT<T1>(2, 8);
    CHECK((a *= 2) == b);
    CHECK(a == b);
    a = ArrayT<T1>(2, 4);
    b = ArrayT<T1>(2, 2);
    CHECK((a /= 2) == b);
    CHECK(a == b);
    a = ArrayT<T1>(2, 4);
    b = ArrayT<T1>(0);
    CHECK((b = a) == a);
    CHECK_THROWS(a /= 0);
}

TEST_CASE("[arrayd] - ArrayT<T> arithmetic ops") {
    ArrayT<T1> a(2, 4);
    ArrayT<T1> b(2, 5);
    a = a + 1;
    CHECK(a == b);
    b = ArrayT<T1>(2, 4);
    a = a - 1;
    CHECK(a == b);
    b = ArrayT<T1>(2, 8);
    a = a * 2;
    CHECK(a == b);
    b = ArrayT<T1>(2, 2);
    a = a / 4;
    CHECK(a == b);
    CHECK_THROWS(a / 0);
}

TEST_CASE("[arrayd] - ArrayT<T> bool operators") {
    ArrayT<T1> a(2, 4);
    ArrayT<T1> b(2, 4);
    CHECK(a == b);
    b = ArrayT<T1>(2, 3);
    CHECK(a != b);
    b = ArrayT<T1>(1, 4);
    CHECK(a != b);
}

TEST_CASE("[arrayd] - ArrayT<T> size & capacity") {
    ArrayT<T1> a(1, 0);
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

typedef Rational T2;
TEST_CASE("[arrayd] - ArrayT<T> ctor") {
    ArrayT<T2> a(3);
    ArrayT<T2> b{ 0, 0, 0 };
    CHECK(a == b);
    a = ArrayT<T2>();
    b = ArrayT<T2>(0);
    CHECK(a == b);
    CHECK_THROWS(a = ArrayT<T2>(-3));
}

TEST_CASE("[arrayd] - ArrayT<T> assignment arithmetic ops") {
    ArrayT<T2> a(2, 4);
    ArrayT<T2> b(2, 5);
    CHECK((a += 1) == b);
    CHECK(a == b);
    a = ArrayT<T2>(2, 4);
    b = ArrayT<T2>(2, 3);
    CHECK((a -= 1) == b);
    CHECK(a == b);
    a = ArrayT<T2>(2, 4);
    b = ArrayT<T2>(2, 8);
    CHECK((a *= 2) == b);
    CHECK(a == b);
    a = ArrayT<T2>(2, 4);
    b = ArrayT<T2>(2, 2);
    CHECK((a /= 2) == b);
    CHECK(a == b);
    a = ArrayT<T2>(2, 4);
    b = ArrayT<T2>(0);
    CHECK((b = a) == a);
    CHECK_THROWS(a /= 0);
}

TEST_CASE("[arrayd] - ArrayT<T> arithmetic ops") {
    ArrayT<T2> a(2, 4);
    ArrayT<T2> b(2, 5);
    a = a + Rational(1);
    CHECK(a == b);
    b = ArrayT<T2>(2, 4);
    a = a - Rational(1);
    CHECK(a == b);
    b = ArrayT<T2>(2, 8);
    a = a * Rational(2);
    CHECK(a == b);
    b = ArrayT<T2>(2, 2);
    a = a / Rational(4);
    CHECK(a == b);
    CHECK_THROWS(a / Rational(0));
}

TEST_CASE("[arrayd] - ArrayT<T> bool operators") {
    ArrayT<T2> a(2, 4);
    ArrayT<T2> b(2, 4);
    CHECK(a == b);
    b = ArrayT<T2>(2, 3);
    CHECK(a != b);
    b = ArrayT<T2>(1, 4);
    CHECK(a != b);
}

TEST_CASE("[arrayd] - ArrayT<T> size & capacity") {
    ArrayT<T2> a(1, 0);
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