#include <iostream>

void solve() {
    int n(0);
    std::cin >> n;
    int prod(0);
    std::cin >> prod;
    for (int i = 1; i < n; ++i) {
        int num(0);
        std::cin >> num;
        prod &= num;
    }
    std::cout << prod << std::endl;
}

int main() {
    int t(0);
    std::cin >> t;
    while (t--) {
        solve();
    }
}
