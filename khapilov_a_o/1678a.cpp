#include <iostream>
#include <vector>

void solve() {
    int n(0);
    std::cin >> n;
    std::vector<int> counter(101, 0);
    bool res(false);
    for (int i = 0; i < n; ++i) {
        int num(0);
        std::cin >> num;
        ++counter[num];
        if (counter[num] > 1) {
            res = true;
        }
    }
    if (counter[0] != 0) {
        std::cout << n - counter[0] << std::endl;
        return;
    }
    if (res) {
        std::cout << n << std::endl;
        return;
    }
    std::cout << n + 1 << std::endl;
}

int main() {
    int t(0);
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
