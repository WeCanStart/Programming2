#include <iostream>
#include <corecrt_math_defines.h>
#include <cmath>
#include <iomanip>

double summation(double x, double epsilon) {
    double sum = 0;
    
    int i = 1;
    double now = 0;
    double power = x;
    do {
        now = power * sin(i * M_PI_4);
        sum += now;
        i++;
        power *= x;
    } while (std::abs(now) >= epsilon);
    return sum;
}

int main() {
    double a = 0, b = 1, sigma = 0.05, epsilon = 0.001;
    double x = a;
    while (std::abs(x - b) < epsilon) {
        std::cout << x << ' ' << summation(x, epsilon) << ' ' << x * sin(M_PI_4) / (1 - 2 * x * cos(M_PI_4)) << std::endl;
        x += sigma;
    }
}
