#include <iostream>
#include <vector>

int max(int a, int b) {
    return ((a > b) ? (a) : b);
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a{ 0 };
    std::vector<int> b{ 0 };
    for (int j = 0; j < n; ++j) {
        int ai(0), bi(0);
        std::cin >> ai >> bi;
        a.push_back(ai);
        b.push_back(bi);
    }
    std::vector<int> tm{};
    for (int j = 0; j < n; ++j) {
        int tmi(0);
        std::cin >> tmi;
        tm.push_back(tmi);
    }
    int time(0);
    for (int j = 1; j < n; ++j) {
        int go = a[j] - b[j - 1] + tm[j - 1];
        time += go;
        time = max((time + (int)std::ceil((b[j] - a[j]) / 2) + 0.1), b[j]);
    }
    int go = a[n] - b[n - 1] + tm[n - 1];
    time += go;
    std::cout << time << std::endl;
}

int main() {
    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}
