#include <darwin_simul/darwin_simul.hpp>
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <numeric>
#include <cmath>
#include <algorithm>

class Plant : public ds::Par {
public:
    Plant(double mass_, double x_, double y_) : ds::Par(mass_, x_, y_, 0) {};
    Plant() = default;
    ~Plant() override = default;

    void writeTo(std::ostream& ostrm) const {
        Par::writeTo(ostrm);
    }
    void readFrom(std::istream& istrm) {
        Par::readFrom(istrm);
    }
};

std::ostream& operator<<(std::ostream& ostrm, const Plant& org) {
    org.writeTo(ostrm);
    return ostrm;
}
std::istream& operator>>(std::istream& istrm, Plant& org) {
    org.readFrom(istrm);
    return istrm;
}

class Herbivore : public ds::Par {
public:
    Herbivore() = default;
    Herbivore(double mass_, double x_, double y_, double viewRange_, double speed_, double danger_, double divisionPeriod_) : ds::Par(mass_, x_, y_, viewRange_), speed(speed_), danger(danger_), divisionPeriod(divisionPeriod_), timeToDivision(divisionPeriod_) {};
    ~Herbivore() override = default;

    void writeTo(std::ostream& ostrm) const {
        Par::writeTo(ostrm);
        ostrm << speed << ' ' << danger << ' ' << divisionPeriod << ' ' << timeToDivision << ' ' << liveTime << ' ';
    }
    void readFrom(std::istream& istrm) {
        Par::readFrom(istrm);
        istrm >> speed >> danger >> divisionPeriod >> timeToDivision >> liveTime;
    }

    void setTarget(const Par* target) {
        has_target = true;
        target_x = target->getX();
        target_y = target->getY();
    }
    void looseTarget() {
        has_target = false;
    }
    bool hasTarget() const {
        return has_target;
    }
    double getTargetX() const {
        return target_x;
    }
    double getTargetY() const {
        return target_y;
    }

    void skipTime(double dt) {
        timeToDeath -= dt;

        if (timeToDivision > 0) {
            timeToDivision -= dt;
        }
        if (timeWithSpeedUp > 0) {
            timeWithSpeedUp -= dt;
        }
        else {
            speedUp = 1;
        }
    }

    bool divisible() {
        return timeToDivision <= 0;
    }
    void resetDivisionTime() {
        timeToDivision = divisionPeriod;
    }

    bool timeOut() {
        return timeToDeath <= 0;
    }
    bool resetDeathTime() { //lifespan
        return timeToDeath = liveTime;
    }

    bool isSpeedUp() const {
        return speedUpTime > 0;
    }
    void setSpeedUp(double alpha) {
        timeWithSpeedUp = speedUpTime;
        speedUp = alpha;
    }
    double speedUpValue() const {
        return speedUp;
    }


    double speed = 1;
    double danger = 1;
    double divisionPeriod = 1;
    double liveTime = 10;
    double speedUpTime = 1;

private:
    bool has_target = false;
    double target_x = 0;
    double target_y = 0;
    double timeToDivision = 1;
    double timeToDeath = 10;
    double timeWithSpeedUp = 0;
    double speedUp = 1;
};

std::ostream& operator<<(std::ostream& ostrm, const Herbivore& org) {
    org.writeTo(ostrm);
    return ostrm;
}
std::istream& operator>>(std::istream& istrm, Herbivore& org) {
    org.readFrom(istrm);
    return istrm;
}

class Predator : public ds::Par {
public:
    Predator() = default;
    Predator(double mass_, double x_, double y_, double viewRange_, double speed_, double danger_, double divisionPeriod_) : ds::Par(mass_, x_, y_, viewRange_), speed(speed_), danger(danger_), divisionPeriod(divisionPeriod_), timeToDivision(divisionPeriod_) {};
    ~Predator() override = default;

    void writeTo(std::ostream& ostrm) const {
        Par::writeTo(ostrm);
        ostrm << speed << ' ' << danger << ' ' << divisionPeriod << ' ' << timeToDivision << ' ';
    }
    void readFrom(std::istream& istrm) {
        Par::readFrom(istrm);
        istrm >> speed >> danger >> divisionPeriod >> timeToDivision;
    }

    void setTarget(const Par* target) {
        has_target = true;
        target_x = target->getX();
        target_y = target->getY();
    }
    void looseTarget() {
        has_target = false;
    }
    bool hasTarget() const {
        return has_target;
    }
    double getTargetX() const {
        return target_x;
    }
    double getTargetY() const {
        return target_y;
    }

    void skipTime(double dt) {
        timeToDeath -= dt;

        if (timeToDivision > 0) {
            timeToDivision -= dt;
        }

        if (timeWithSpeedUp > 0) {
            timeWithSpeedUp -= dt;
        }
        else {
            speedUp = 1;
        }

        if (timeWithStunn > 0) {
            timeWithStunn -= dt;
        }
    }

    bool divisible() const {
        return timeToDivision <= 0;
    }
    void resetDivisionTime() {
        timeToDivision = divisionPeriod;
    }

    bool timeOut() const {
        return timeToDeath <= 0;
    }
    bool resetDeathTime() { //lifespan
        return timeToDeath = liveTime;
    }

    bool isSpeedUp() const {
        return speedUpTime > 0;
    }
    void setSpeedUp(double alpha) {
        timeWithSpeedUp = speedUpTime;
        speedUp = alpha;
    }
    double speedUpValue() const {
        return speedUp;
    }

    bool isStanned() const {
        return timeWithStunn > 0;
    }
    void setStann() {
        timeWithStunn = stunnTime;
    }

    double speed = 1;
    double danger = 1;
    double divisionPeriod = 1;
    double liveTime = 15;
    double speedUpTime = 1;
    double stunnTime = 1;

private:
    bool has_target = false;
    double target_x = 0;
    double target_y = 0;
    double timeToDivision = 1;
    double timeToDeath = 15;
    double timeWithSpeedUp = 1;
    double speedUp = 1;
    double timeWithStunn = 0;
};

std::ostream& operator<<(std::ostream& ostrm, const Predator& org) {
    org.writeTo(ostrm);
    return ostrm;
}
std::istream& operator>>(std::istream& istrm, Predator& org) {
    org.readFrom(istrm);
    return istrm;
}

std::random_device rd;
unsigned int seed = rd();
std::mt19937 gen(seed);
std::uniform_real_distribution<> dis(0, 1);

template<>
void ds::calculations(Herbivore* p, const TArray<Plant, Herbivore, Predator>& arr, double dt) {
    double maxProfit{ 0 };
    double profit{ 0 };
    auto plntVec = arr.getByType<Plant>();
    for (auto& plnt : plntVec) {
        profit = plnt->getMass() * plnt->getMass() / ((plnt->getX() - p->getX()) * (plnt->getX() - p->getX()) + (plnt->getY() - p->getY()) * (plnt->getY() - p->getY()));
        if (profit > maxProfit) {
            maxProfit = profit;
            p->setTarget(plnt);
        }
    }
    p->looseMass((p->danger / 255 + p->speed / 768 + p->viewRange / 768 + p->getMass() / 200 + 0.03) * dt * p->getMass());

    if (p->timeOut()) {
        p->die();
    }

    p->skipTime(dt);
}

template<>
void ds::calculations(Predator* p, const TArray<Plant, Herbivore, Predator>& arr, double dt) {
    if (p->getMass() < 1.5 * p->getStartMass()) {
        double maxProfit{ 0 };
        double profit{ 0 };
        auto hrbvrVec = arr.getByType<Herbivore>();
        for (auto& hrbvr : hrbvrVec) {
            profit = hrbvr->getMass() * hrbvr->getMass() / ((hrbvr->getX() - p->getX()) * (hrbvr->getX() - p->getX()) + (hrbvr->getY() - p->getY()) * (hrbvr->getY() - p->getY()));
            if (profit > maxProfit) {
                maxProfit = profit;
                p->setTarget(hrbvr);
            }
        }
        auto prdtrVec = arr.getByType<Predator>();
        for (auto& prdtr : prdtrVec) {
            if (std::max(p->danger, prdtr->danger) / std::min(p->danger, prdtr->danger) +
                std::max(p->speed, prdtr->speed) / std::min(p->speed, prdtr->speed) +
                std::max(p->viewRange, prdtr->viewRange) / std::min(p->viewRange, prdtr->viewRange) < 3.3) continue;
            profit = prdtr->getMass() * prdtr->getMass() / ((prdtr->getX() - p->getX()) * (prdtr->getX() - p->getX()) + (prdtr->getY() - p->getY()) * (prdtr->getY() - p->getY()));
            if (profit > maxProfit) {
                maxProfit = profit;
                p->setTarget(prdtr);
            }
        }
    }

    p->looseMass((p->danger / 255 + p->speed / 768 + p->viewRange / 768 + p->getMass() / 200 + 0.03) * dt * p->getMass() / 10);

    if (p->timeOut()) {
        p->die();
    }

    p->skipTime(dt);
}


template<>
void ds::move(Herbivore* p, double dt) {
    if (p->hasTarget()) {
        double dist_x = p->getTargetX() - p->getX();
        double dist_y = p->getTargetY() - p->getY();
        double dist = sqrt(dist_x * dist_x + dist_y * dist_y);
        double ds = p->speed * dt * p->speedUpValue();
        if (dist == 0) return;
        p->moveX(ds * dist_x / dist);
        p->moveY(ds * dist_y / dist);
        p->looseMass(p->speed * ds * p->getMass() / 331000);
        p->looseTarget();
    }
}

template<>
void ds::move(Predator* p, double dt) {
    if (p->hasTarget()) {
        if (!p->isStanned()) {
            double dist_x = p->getTargetX() - p->getX();
            double dist_y = p->getTargetY() - p->getY();
            double dist = sqrt(dist_x * dist_x + dist_y * dist_y);
            double ds = p->speed * dt * p->speedUpValue();
            if (dist == 0) return;
            p->moveX(ds * dist_x / dist);
            p->moveY(ds * dist_y / dist);
            p->looseMass(p->speed * ds * p->getMass() / 331000000);
        }
        p->looseTarget();
    }
}


template<>
void ds::collision(Plant* plnt, Herbivore* hrbvr) {
    hrbvr->eat(plnt);
}

template<>
void ds::collision(Herbivore* hrbvr, Predator* prdtr) {
    if (prdtr->isStanned() || prdtr->getMass() >= 1.5 * prdtr->getStartMass()) return;
    double hrbvr_v = hrbvr->viewRange * dis(gen);
    double prdtr_v = prdtr->viewRange * dis(gen);
    if (prdtr_v > hrbvr_v) {
        double hrbvr_d = hrbvr->danger * dis(gen);
        double prdtr_d = prdtr->danger * dis(gen);
        if (prdtr_d > hrbvr_d) {
            prdtr->looseMass(0.5 * hrbvr_d / prdtr_d * prdtr->getMass());
            prdtr->eat(hrbvr);
        }
        else {
            prdtr->looseMass(prdtr->getMass() * (1 - prdtr_d / hrbvr_d)); // add
            hrbvr->setSpeedUp(1 / 3.1416 * atan(hrbvr_d / prdtr_d - 1) + 1);
            prdtr->setStann();
        }
    }
    else {
        double hrbvr_s = hrbvr->speed * dis(gen);
        double prdtr_s = prdtr->speed * dis(gen);
        if (prdtr_s > hrbvr_s) {
            double hrbvr_d = hrbvr->danger * dis(gen);
            double prdtr_d = prdtr->danger * dis(gen);
            if (prdtr_d > hrbvr_d) {
                prdtr->looseMass(0.5 * hrbvr_d / prdtr_d * prdtr->getMass());
                prdtr->eat(hrbvr);
            }
            else {
                prdtr->looseMass(prdtr->getMass() * (1 - prdtr_d / hrbvr_d)); // add
                hrbvr->setSpeedUp(1 / 3.1416 * atan(hrbvr_d / prdtr_d - 1) + 1);
                prdtr->setStann();
            }
        }
        else {
            hrbvr->setSpeedUp(1 / 3.1416 * atan(hrbvr_s / prdtr_s - 1) + 1);
            prdtr->setStann();
        }
    }
}

template<>
void ds::collision(Predator* prdtr, Herbivore* hrbvr) {
    if (prdtr->isStanned() || prdtr->getMass() >= 1.5 * prdtr->getStartMass()) return;
    double hrbvr_v = hrbvr->viewRange * dis(gen);
    double prdtr_v = prdtr->viewRange * dis(gen);
    if (prdtr_v > hrbvr_v) {
        double hrbvr_d = hrbvr->danger * dis(gen);
        double prdtr_d = prdtr->danger * dis(gen);
        if (prdtr_d > hrbvr_d) {
            prdtr->looseMass(0.5 * hrbvr_d / prdtr_d * prdtr->getMass());
            prdtr->eat(hrbvr);
        }
        else {
            prdtr->looseMass(prdtr->getMass() * (1 - prdtr_d / hrbvr_d)); // add
            hrbvr->setSpeedUp(1 / 3.1416 * atan(hrbvr_d / prdtr_d - 1) + 1);
            prdtr->setStann();
        }
    }
    else {
        double hrbvr_s = hrbvr->speed * dis(gen);
        double prdtr_s = prdtr->speed * dis(gen);
        if (prdtr_s > hrbvr_s) {
            double hrbvr_d = hrbvr->danger * dis(gen);
            double prdtr_d = prdtr->danger * dis(gen);
            if (prdtr_d > hrbvr_d) {
                prdtr->looseMass(0.5 * hrbvr_d / prdtr_d * prdtr->getMass());
                prdtr->eat(hrbvr);
            }
            else {
                prdtr->looseMass(prdtr->getMass() * (1 - prdtr_d / hrbvr_d)); // add
                hrbvr->setSpeedUp(1 / 3.1416 * atan(hrbvr_d / prdtr_d - 1) + 1);
                prdtr->setStann();
            }
        }
        else {
            hrbvr->setSpeedUp(1 / 3.1416 * atan(hrbvr_s / prdtr_s - 1) + 1);
            prdtr->setStann();
        }
    }
}

template<>
void ds::collision(Predator* prdtr1, Predator* prdtr2) {
    if (std::max(prdtr1->danger, prdtr2->danger) / std::min(prdtr1->danger, prdtr2->danger) +
        std::max(prdtr1->speed, prdtr2->speed) / std::min(prdtr1->speed, prdtr2->speed) +
        std::max(prdtr1->viewRange, prdtr2->viewRange) / std::min(prdtr1->viewRange, prdtr2->viewRange) < 3.3) return;
    double prdtr_d1 = prdtr1->danger * dis(gen);
    double prdtr_d2 = prdtr2->danger * dis(gen);
    if (prdtr_d1 > prdtr_d2) {
        prdtr1->looseMass(0.5 * prdtr_d2 / prdtr_d1 * prdtr1->getMass());
        prdtr1->eat(prdtr2);
    }
    else {
        prdtr2->looseMass(0.5 * prdtr_d1 / prdtr_d2 * prdtr2->getMass());
        prdtr2->eat(prdtr1);
    }
}

template<>
void ds::collision(Herbivore* hrbvr, Plant* plnt) {
    hrbvr->eat(plnt);
}


template<>
void ds::reproduction(Herbivore* p, std::vector<Herbivore>& alives) {
    if (!p->divisible() || p->getMass() <= p->getStartMass()) return; //update below
    p->looseMass(p->getMass() / 2);
    p->resetDivisionTime();
    Herbivore hrbvr = *p;
    hrbvr.resetDeathTime();
    hrbvr.moveX(12 * hrbvr.radius() * (dis(gen) - 0.5));
    hrbvr.moveY(12 * hrbvr.radius() * (dis(gen) - 0.5));
    alives.resize(1);
    hrbvr.danger *= (0.95 + 0.1 * dis(gen));
    hrbvr.viewRange *= (0.95 + 0.1 * dis(gen));
    hrbvr.speed *= (0.95 + 0.1 * dis(gen));
    alives[0] = hrbvr;
}

template<>
void ds::reproduction(Predator* p, std::vector<Predator>& alives) {
    if (!p->divisible() || p->getMass() <= p->getStartMass()) return;
    p->looseMass(p->getMass() / 2);
    p->resetDivisionTime();
    Predator prdtr = *p;
    prdtr.resetDeathTime();
    prdtr.moveX(12 * prdtr.radius() * (dis(gen) - 0.5));
    prdtr.moveY(12 * prdtr.radius() * (dis(gen) - 0.5));
    alives.resize(1);
    prdtr.danger *= (0.95 + 0.1 * dis(gen));
    prdtr.viewRange *= (0.95 + 0.1 * dis(gen));
    prdtr.speed *= (0.95 + 0.1 * dis(gen));
    alives[0] = prdtr;
}

template<>
void ds::spawn(TArray<Plant, Herbivore, Predator>& alives, double massLeft, double wid, double high, double dt) {
    std::vector<Plant> plants;
    while (massLeft > 10) {
        plants.push_back(Plant{ 10, wid * dis(gen), high * dis(gen) });
        massLeft -= 10;
    }
    alives.putByType(plants);
}

template<>
void ds::spawn(TArray<Plant, Herbivore>& alives, double massLeft, double wid, double high, double dt) {
    std::vector<Plant> plants;
    while (massLeft > 10) {
        plants.push_back(Plant{ 10, wid * dis(gen), high * dis(gen) });
        massLeft -= 10;
    }
    alives.putByType(plants);
}