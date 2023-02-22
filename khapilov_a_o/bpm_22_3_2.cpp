#include <iostream>

int main() {
    long number = 0;
    long number_in_area = 0;
    double x = 0.0;
    double y = 0.0;
    while (std::cin.good()) {
        std::cin >> x >> y;
        ++number;
        if (x * x + y * y >= 1 && y >= -1 && y <= 1 && x >= -2 && x <= 2) {
            ++number_in_area;
        }
    }
    std::cout << static_cast<double>(number_in_area) / number;
    return 0;
}