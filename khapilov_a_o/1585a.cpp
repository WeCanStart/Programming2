#include <iostream>
#include <limits>

void solve() {
    int n;
    std::cin >> n;
    int h = 1;
    bool prev = 0;
    bool now = 0;
    std::cin >> now;
    if (now) ++h;
    prev = now;
    for (int i = 1; i < n; ++i) {
        std::cin >> now;
        if (now) {
            if (prev) {
                h += 5;
            }
            else {
                ++h;
            }
        }
        else {
            if (!prev) {
                std::cout << -1 << std::endl;
                for (int j = 0; j < n - i - 1; ++j) std::cin >> now;
                return;
            }
        }
        prev = now;
    }
    std::cout << h << std::endl;
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
