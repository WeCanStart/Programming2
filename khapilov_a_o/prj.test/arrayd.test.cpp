#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <rational/rational.hpp>

TEST_CASE("[rational] - Rational ctor") {
  CHECK(Rational() == Rational(0, 1));
  CHECK(Rational(3) == Rational(3, 1));
  CHECK(Rational(-3) == Rational(-3, 1));
  CHECK(Rational(10, 6) == Rational(5, 3));
  CHECK(Rational(-10, 6) == Rational(-5, 3));
  CHECK(Rational(10, -6) == Rational(-5, 3));
  CHECK(Rational(-10, -6) == Rational(5, 3));
  CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("[rational] - Rational assignment arithmetic ops") {
    Rational a;
    a = Rational(1, 2);
    CHECK((a += Rational(1, 3)) == Rational(5, 6));
    CHECK(a == Rational(5, 6));
    a = Rational(1, 2);
    CHECK((a -= Rational(1, 3)) == Rational(1, 6));
    CHECK(a == Rational(1, 6));
    a = Rational(1, 2);
    CHECK((a *= Rational(1, 3)) == Rational(1, 6));
    CHECK(a == Rational(1, 6));
    a = Rational(1, 2);
    CHECK((a /= Rational(1, 3)) == Rational(3, 2));
    CHECK(a == Rational(3, 2));
    a = Rational(1, 2);
    CHECK(a++ == Rational(1, 2));
    CHECK(a == Rational(3, 2));
    a = Rational(1, 2);
    CHECK(++a == Rational(3, 2));
    CHECK(a == Rational(3, 2));
    a = Rational(1, 2);
    Rational b;
    CHECK((b = a) == a);
    CHECK_THROWS(Rational(1, 1) /= Rational(0, 1));
}

TEST_CASE("[rational] - Rational arithmetic ops") {
    CHECK(Rational(1, 2) + Rational(1, 3) == Rational(5, 6));
    CHECK(Rational(1, 2) - Rational(1, 3) == Rational(1, 6));
    CHECK(Rational(1, 2) * Rational(1, 3) == Rational(1, 6));
    CHECK(Rational(1, 2) / Rational(1, 3) == Rational(3, 2));
    CHECK_THROWS(Rational(1, 1) / Rational(0, 1));
}

TEST_CASE("[rational] - Rational extras") {
    CHECK(sqr(Rational(2, 3)) == Rational(4, 9));
    CHECK(pow(Rational(2, 3), -3) == Rational(27, 8));
    CHECK(pow(Rational(2, 3), 0) == Rational(1, 1));
    CHECK(pow(Rational(2, 3), 3) == Rational(8, 27));
    CHECK_THROWS(Rational(1, 1) / Rational(0, 1));
}

TEST_CASE("[rational] - Rational bool operators") {
    CHECK(Rational(1, 2) > Rational(1, 3));
    CHECK(Rational(1, 2) >= Rational(1, 3));
    CHECK(Rational(1, 3) < Rational(1, 2));
    CHECK(Rational(1, 3) <= Rational(1, 2));
    CHECK(Rational(1, 2) == Rational(1, 2));
    CHECK(Rational(1, 3) != Rational(1, 2));
}
