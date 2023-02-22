#include <iostream>
#include <cmath>


struct RDec2d {
    double x = 0;
    double y = 0;
    
    double norm() {
        return std::sqrt(x * x + y * y);
    }
    double angle() {
        return std::atan2(y, x);
    }
};

double dot(RDec2d lhs, RDec2d rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
double cos_between(RDec2d lhs, RDec2d rhs) {
    return std::abs(dot(lhs, rhs)) / (lhs.norm() * rhs.norm());
}

struct RPol2d {
    double r = 0;
    double phi = 0;
};


RPol2d Rec_to_Pol(RDec2d vec) {
    RPol2d ans(vec.norm(), vec.angle());
    return ans;
}

RDec2d Rec_to_Pol(RPol2d vec) {
    RDec2d ans(vec.r * std::cos(vec.phi), vec.r * std::sin(vec.phi));
    return ans;
}


int main() {
    RDec2d vec1_d(3, 4), vec2_d(5, 12);
    std::cout << vec1_d.norm() << ' ' << vec1_d.angle() << ' ' << dot(vec1_d, vec2_d) << ' ' << cos_between(vec1_d, vec2_d) << std::endl;
    RPol2d vec1_p = Rec_to_Pol(vec1_d), vec2_p = Rec_to_Pol(vec2_d);
    std::cout << vec1_p.r << ' ' << vec1_p.phi << ' ' << std::cos(vec1_p.phi - vec2_p.phi) * vec1_p.r * vec2_p.r << ' ' << std::cos(vec1_p.phi - vec2_p.phi) << std::endl;
    return 0;
}
