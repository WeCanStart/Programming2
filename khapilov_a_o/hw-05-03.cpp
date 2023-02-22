#include <iostream>
#include <cmath>
#include <iomanip>

double summation(double x, double epsilon) {
    double sum = 0;

    int i = 0;
    double now = 0;
    double power = 1;
    double factorial = 1;
    do {
        now = power / factorial;
        sum += now;
        i++;
        power *= 2 * x;
        factorial *= i;
    } while (std::abs(now) >= epsilon);
    return sum;
}

int main() {
    double a = 0, b = 1, sigma = 0.1, epsilon = 0.0001;
    double x = a;
    while (std::abs(x - b) < epsilon) {
        std::cout << x << ' ' << summation(x, epsilon) << ' ' << exp(2 * x) << std::endl;
        x += sigma;
    }
}
