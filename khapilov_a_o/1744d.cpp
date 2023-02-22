#include <iostream>
#include <vector>
#include <algorithm>

int two(int n) {
    int ans = 0;
    while (!(n & 1)) {
        n /= 2;
        ++ans;
    }
    return ans;
}

void solve() {
    int n = 0;
    std::cin >> n;
    int c = 0;
    for (int i = 0; i < n; ++i) {
        int num = 0;
        std::cin >> num;
        c += two(num);
    }
    if (c >= n) {
        std::cout << 0 << std::endl;
    }
    else {
        int sum_power_of_index = 0;
        int oper = 0;
        int start = 1;
        for (int i = 0; i < n; ++i) {
            if (start * 2 > n) {
                break;
            }
            start *= 2;
        }
        while (start > 1) {
            for (int i = start; i <= n; i += start) {
                if ((i / start) % 2 == 0) {
                    continue;
                }
                int number = two(i);
                if (number > 0) {
                    ++oper;
                }
                sum_power_of_index += two(i);
                if (c + sum_power_of_index >= n) {
                    std::cout << oper << std::endl;
                    return;
                }
            }
            start /= 2;
        }
        
        std::cout << -1 << std::endl;
    }
    return;
}

int main()
{
    int t = 0;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
