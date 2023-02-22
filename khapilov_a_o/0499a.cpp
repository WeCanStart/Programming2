#include <iostream>
#include <vector>
#include <algorithm>
#include <string>




int max(int l, int r) {
    return (l > r) ? l : r;
}
int min(int l, int r) {
    return (l < r) ? l : r;
}




int main() {
    int n = 0;
    int x = 0;
    std::cin >> n >> x;
    int m = 1;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int l = 0, r = 0;
        std::cin >> l >> r;
        int jmp = l - m;
        ans += jmp % x;
        ans += r - l + 1;
        m = r + 1;
    }
    std::cout << ans;
    return 0;
}
