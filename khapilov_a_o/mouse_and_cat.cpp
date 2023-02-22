#include <iostream>
#include <cmath>
#include <vectors.h>

double max(double lhs, double rhs) {
    return (lhs > rhs) ? lhs : rhs;
}


int main() {
    RDec2d r_mouse, r_cat;
    std::cin >> r_mouse.x >> r_mouse.y >> r_cat.x >> r_cat.y;
    RDec2d v_mouse;
    std::cin >> v_mouse.x >> v_mouse.y;
    double v_full_cat = 0;
    std::cin >> v_full_cat;
    RDec2d vec_cat_to_mouse = r_mouse - r_cat;
    RDec2d v_cat = norm(vec_cat_to_mouse) * v_full_cat;
    double c_c;
    std::cin >> c_c;

    bool eaten = false;
    bool hidden = false;
    bool escaped = false;
    if (max(len(v_mouse), v_full_cat) < std::numeric_limits<double>::epsilon()) {
        std::cout << "That can continuous infinitly";
        return 0;
    }
    double dist_before = 0;
    double dist_now = len(vec_cat_to_mouse);
    double dt = 0.01 / (max(len(v_mouse), v_full_cat) * (1 + 9 / exp(dist_now)));
    double t = 0;
    while (!eaten && !hidden && !escaped) {
        std::swap(dist_before, dist_now);
        r_mouse += v_mouse * dt;
        r_cat += v_cat * dt;
        vec_cat_to_mouse = r_mouse - r_cat;
        v_cat = norm(vec_cat_to_mouse) * v_full_cat;
        dist_now = len(vec_cat_to_mouse);
        if (dist_now <= c_c) {
            eaten = true;
        }
        if (r_mouse.y <= 0) {
            hidden = true;
        }
        if (dist_now <= dist_before) {
            escaped = true;
        }
        dt = 0.01 / (max(len(v_mouse), v_full_cat) * (1 + 9 / exp(dist_now)));
        t += dt;
    }
    if (eaten && (hidden || escaped)) {
        std::cout << "Decreas base dt, please";
        return 0;
    }
    if (eaten) {
        std::cout << "Mouse was eaten in " << t << " seconds";
    }
    if (hidden) {
        std::cout << "Mouse hidden in " << t << " seconds";
    }
    if (escaped) {
        std::cout << "Mouse escaped in " << t << " seconds";
    }
    return 0;
}
