#include <iostream>
#include <string>
#include <vector>

void solve() {
    int n = 0;
    std::cin >> n;
    std::string s = "";
    std::cin >> s;
    int g = 0;
    std::cin >> g;
    std::vector<bool> sg(200, false);
    for (int i = 0; i < g; ++i) {
        char sym = 0;
        std::cin >> sym;
        sg[(int)sym - (int)'a'] = true;
    }
    int now(0), prev(-1);
    for (int i = 0; i < n; ++i) {
        now++;
        if (sg[(int)s[i] - (int)'a']) {
            if (prev == -1) {
                prev = now - 1;
            }
            else {
                if (now - 1 >= prev) {
                    prev = now;
                }
            }
            now = 0;
        }
    }
    if (prev == -1) {
        std::cout << 0 << std::endl;
    }
    else {
        std::cout << prev << std::endl;
    }
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    int t = 0;
    std::cin >> t;
    while (t--) solve();
    return 0;
}