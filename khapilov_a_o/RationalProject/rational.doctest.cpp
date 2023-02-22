#include <rational/rational.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <iostream>

Rational a(2, 3);
Rational b(1, 2);

int32_t n{ 6 };

Rational sum(7, 6);
Rational dif(1, 6);
Rational prod(1, 3);
Rational dev(4, 3);
Rational mod(1, 6);

TEST_CASE("checking arithmetic") {
    CHECK(a + b == sum);
    CHECK(a - b == dif);
    CHECK(a * b == prod);
    CHECK(a / b == dev);
    CHECK(a % b == mod);
}

Rational thirdPow_a(8, 27);
Rational sqr_a(4, 9);

TEST_CASE("checking castom") {
    CHECK(pow(a, 3) == thirdPow_a);
    CHECK(sqr(a) == sqr_a);
}

bool less = false;
bool equal = false;
bool bigger = true;

TEST_CASE("checking boolean") {
    CHECK((a < b) == less);
    CHECK((a == b) == equal);
    CHECK((a > b) == bigger);
}
