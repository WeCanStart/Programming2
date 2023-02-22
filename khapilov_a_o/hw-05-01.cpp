#include <iostream>
#include <cmath>
#include <iomanip>

double summation(double x, double epsilon) {
    double sum = 0;
    
    int i = 0;
    double now = 0;
    int sign = 1;
    double power = 1;
    double factorial = 1;
    do {
        now = sign * power / factorial;
        sum += now;
        i++;
        sign *= -1;
        power *= x * x;
        factorial *= (2 * i - 1) * 2 * i;
    } while (std::abs(now) >= epsilon);
    return sum;
}

int main() {
    double a = -1, b = 1, sigma = 0.1, epsilon = 0.001;
    double x = a;
    while (std::abs(x - b) > epsilon) {
        std::cout << x << ' ' << summation(x, epsilon) << ' ' << cos(x) << std::endl;
        x += sigma;
    }
}
