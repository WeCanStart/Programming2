#include <iostream>

double find(double x, double eps) {
    double now_term = 1;
    double sum = 1;
    for (int i = 1; now_term >= eps; ++i) {
        now_term = now_term * 2.0 * x / i;
        sum += now_term;
    }
    return sum;
}

int main()
{
    double x = 0.1;
    const double x_stop = 1;
    const double delta_x = 0.05;
    const double eps = 0.0001;
    while (std::abs(x - x_stop) > eps) {
        std::cout << find(x, eps) << std::endl;
        x += delta_x;
    }
    std::cout << find(x, eps) << std::endl;
    return 0;
}
