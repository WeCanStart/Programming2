#include <iostream>
#include <string>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void solve() {
    std::string str;
    std::cin >> str;
    int set_one = 0, set_zero = str.size() - 1;
    bool first_zero = true;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == '1') {
            set_one = i;
        }
        if (str[i] == '0' ) {
            set_zero = i;
            std::cout << (set_zero - set_one + 1) << std::endl;
            return;
        }
    }
    std::cout << (set_zero - set_one + 1) << std::endl;
}

int main() {
    int t = 0;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
