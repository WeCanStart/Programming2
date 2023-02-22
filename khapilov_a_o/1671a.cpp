#include <iostream>
#include <vector>
#include <string>

void solve() {
    std::string str;
    std::cin >> str;
    int n = str.size();
    std::vector<bool> s;
    for (int i = 0; i < n; ++i) {
        char l = str[i];
        if (l == 'a') {
            s.push_back(0);
        }
        else {
            s.push_back(1);
        }
    }
    int c(1);
    bool t(0);
    if (s[0]) {
        t = 1;
    }
    else {
        t = 0;
    }
    for (int i = 1; i < n; ++i) {
        if (s[i] != t) {
            if (c == 1) {
                std::cout << "NO" << std::endl;
                return;
            }
            t = s[i];
            c = 0;
        }
        ++c;
    }
    if (c == 1) {
        std::cout << "NO" << std::endl;
        return;
    }
    std::cout << "YES" << std::endl;
    return;
}

int main() {
    int t(0);
    std::cin >> t;
    while (t--) {
        solve();
    }
}
