#include <iostream>
#include <string>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void solve() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::string str;
    std::cin >> str;
    int s = 0;
    for (int i = 0; i < k; ++i) {
        if (str[i] == 'B') {
            s += 1;
        }
    }
    int sm = s;
    for (int i = 1; i < n - k + 1; ++i) {
        if (str[i - 1] == 'B') {
            s -= 1;
        }
        if (str[i + k - 1] == 'B') {
            s += 1;
        }
        sm = max(s, sm);
    }
    std::cout << k - sm << std::endl;
}

int main() {
    int t = 0;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
