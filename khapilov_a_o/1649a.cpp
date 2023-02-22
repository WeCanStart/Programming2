#include <iostream>
#include <vector>

int max(int a, int b) {
    return ((a > b) ? (a) : b);
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<bool> wg;
    for (int j = 0; j < n; j++) {
        bool now = false;
        std::cin >> now;
        wg.push_back(now);
    }
    int l = 0;
    int r = 0;
    for (int j = 1; j < n; j++) {
        if (!wg[j]) {
            l = j - 1;
            break;
        }
        if (j == n - 1) {
            std::cout << 0;
            return;
        }
    }
    for (int j = n - 2; j >= 0; j--) {
        if (!wg[j]) {
            r = j + 1;
            break;
        }
        if (j == 0) {
            std::cout << 0;
            return;
        }
    }
    std::cout << r - l << std::endl;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}
