#include <pl_he_pr_simul/pl_he_pr_simul.hpp>
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <chrono>
#include <random>
#include <fstream>
#include <string>

ds::DarwinSimulator<Plant, Herbivore> s(0.01, 1000, 1000, 11);

TEST_CASE("Comparing before addition") {
    SUBCASE("Plants") {
        std::vector<Plant*> plnts = s.get<Plant>();
        CHECK((plnts.size() == 0) == true);
    }
    SUBCASE("Herbivores") {
        std::vector<Herbivore*> plnts = s.get<Herbivore>();
        CHECK((plnts.size() == 0) == true);
    }
}

TEST_CASE("Comparing after addition") {
    SUBCASE("Plants") {
        s.addAlive<Plant>(Plant(10, 20, 30));
        std::vector<Plant*> plnts = s.get<Plant>();
        CHECK(plnts.size() == 1);
        CHECK(plnts[0]->getMass() == 10);
        CHECK(plnts[0]->getX() == 20);
        CHECK(plnts[0]->getY() == 30);
    }
    SUBCASE("Herbivores") {
        s.addAlive<Herbivore>(Herbivore(10, 80, 90, 40, 50, 60, 70));
        std::vector<Herbivore*> hrbvrs = s.get<Herbivore>();
        CHECK(hrbvrs.size() == 1);
        CHECK(hrbvrs[0]->getMass() == 10);
        CHECK(hrbvrs[0]->getX() == 80);
        CHECK(hrbvrs[0]->getY() == 90);
        CHECK(hrbvrs[0]->viewRange == 40);
        CHECK(hrbvrs[0]->speed == 50);
        CHECK(hrbvrs[0]->danger == 60);
        CHECK(hrbvrs[0]->divisionPeriod == 70);
    }
}

TEST_CASE("Comparing after update") {
    s.update();
    SUBCASE("Plants") {
        std::vector<Plant*> plnts = s.get<Plant>();
        std::mt19937 gen_test(seed);
        Plant plnt_test(Plant{ 10, 1000 * dis(gen_test), 1000 * dis(gen_test) });
        CHECK(plnts.size() == 2);
        CHECK((plnts[0]->getX() == plnt_test.getX() || plnts[1]->getX() == plnt_test.getX()) == true);
        CHECK((plnts[0]->getY() == plnt_test.getY() || plnts[1]->getY() == plnt_test.getY()) == true);
    }
    SUBCASE("Herbivores") {
        std::vector<Herbivore*> hrbvrs = s.get<Herbivore>();
        CHECK(hrbvrs.size() == 1);
    }
}