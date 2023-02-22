#include <iostream>
#include <string>
#include <vector>

void solve() {
    int a = 0, b = 0;
    std::cin >> a >> b;
    std::vector<int> ab = {a, b};
    std::string s = "";
    std::cin >> s;
    int n = s.size();
    for (int i = 0; i < n / 2; i++) {
        char& l = s[i], &r = s[n - i - 1];
        if (l == '?') {
            if (r != '?') {
                l = r;
                ab[(int)r - (int)'0'] -= 2;
            }
        }
        else {
            if (r == '?') {
                r = l;
                ab[(int)l - (int)'0'] -= 2;
            }
            else {
                if (l == r) {
                    ab[(int)l - (int)'0']-=2;
                }
                else {
                    std::cout << -1 << std::endl;
                    return;
                }
            }
        }
    }
    if (n % 2 != 0) {
        if (s[n / 2] == '?') {
            if (ab[0] % 2 == 1) {
                ab[0]--;
                s[n / 2] = '0';
            }
            else {
                if (ab[1] % 2 == 1) {
                    ab[1]--;
                    s[n / 2] = '1';
                }
                else {
                    std::cout << -1 << std::endl;
                    return;
                }
            }
        }
        else {
            ab[(int)s[n / 2] - (int)'0']--;
        }
    }
    if (ab[0] % 2 != 0 || 0 != ab[1] % 2) {
        std::cout << -1 << std::endl;
        return;
    }
    int i = 0;
    while (ab[0] > 0) {
        if (i == n / 2) {
            std::cout << -1 << std::endl;
            return;
        }
        if (s[i] == '?') {
            s[i] = '0';
            s[n - i - 1] = '0';
            ab[0] -= 2;
        }
        i++;
    }
    while (ab[1] > 0) {
        if (i == n / 2) {
            std::cout << -1 << std::endl;
            return;
        }
        if (s[i] == '?') {
            s[i] = '1';
            s[n - i - 1] = '1';
            ab[1] -= 2;
        }
        i++;
    }
    if (s.find('?') != std::string::npos) {
        std::cout << -1 << std::endl;
        return;
    }
    std::cout << s << std::endl;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t = 0;
    std::cin >> t;
    while (t--) solve();
    return 0;
}