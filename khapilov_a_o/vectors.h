struct RDec2d {
    double x = 0;
    double y = 0;
};


double len(RDec2d tmp) {
    return std::sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
}

RDec2d norm(RDec2d tmp) {
    tmp.x /= len(tmp);
    tmp.y /= len(tmp);
    return tmp;
}

double angle(RDec2d tmp) {
    return std::atan2(tmp.y, tmp.x);
}

RDec2d operator+ (RDec2d const lhs, RDec2d const rhs) {
    RDec2d tmp(lhs);
    tmp.x += rhs.x;
    tmp.y += rhs.y;
    return tmp;
}

RDec2d operator* (RDec2d const lhs, double const rhs) {
    RDec2d tmp(lhs);
    tmp.x *= rhs;
    tmp.y *= rhs;
    return tmp;
}

RDec2d operator- (RDec2d const lhs, RDec2d const rhs) {
    RDec2d tmp(lhs);
    tmp.x -= rhs.x;
    tmp.y -= rhs.y;
    return tmp;
}

void operator+= (RDec2d& const lhs, RDec2d const rhs) {
    RDec2d tmp(lhs);
    lhs.x += rhs.x;
    lhs.y += rhs.y;
}

void operator-= (RDec2d& const lhs, RDec2d const rhs) {
    lhs.x -= rhs.x;
    lhs.y -= rhs.y;
}

double dot(RDec2d lhs, RDec2d rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}
double cos_between(RDec2d lhs, RDec2d rhs) {
    return std::abs(dot(lhs, rhs)) / (len(lhs) * len(rhs));
}

struct RPol2d {
    double r = 0;
    double phi = 0;
};


RPol2d Rec_to_Pol(RDec2d vec) {
    RPol2d ans(len(vec), angle(vec));
    return ans;
}

RDec2d Rec_to_Pol(RPol2d vec) {
    RDec2d ans(vec.r * std::cos(vec.phi), vec.r * std::sin(vec.phi));
    return ans;
}