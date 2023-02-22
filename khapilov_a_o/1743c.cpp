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
    int t = 0;
    std::cin >> t;
    while (t--) {
        int n = 0;
        std::cin >> n;
        std::string top;
        std::cin >> top;
        top = '0' + top;
        std::vector<int> box(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            std::cin >> box[i];
        }
        int ans = 0;
        int prev_zero = -1;
        int min_one = std::numeric_limits<int>::max();
        for (int pointer = 0; pointer <= n; ++pointer) {
            if (top[pointer] == '0') {
                if (prev_zero != -1 && top[pointer - 1] == '1') {
                    ans += max(0, box[prev_zero] - min_one);
                }
                prev_zero = pointer;
                min_one = std::numeric_limits<int>::max();
            }
            else {
                min_one = min(min_one, box[pointer]);
                ans += box[pointer];
            }
        }
        if (prev_zero != -1 && top[n] == '1') {
            ans += max(0, box[prev_zero] - min_one);
        }
        std::cout << ans << std::endl;
    }
  return 0;
}
