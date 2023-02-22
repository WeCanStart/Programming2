#include <iostream>
#include <string>
#include <vector>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void solve() {
    int n = 0;
    char c = 0;
    std::string str = "";
    std::cin >> n >> c;
    std::cin >> str;
    std::vector<int> vec(str.size(), -1);
    int start = 0;
    int ma = 0;
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == 'g') {
            start = i;
            vec[i] = 0;
        }
    }
    for (int i = start - 1; i > start - (int)str.size(); --i) {
        if (vec[(i + str.size()) % str.size()] == -1) {
            vec[(i + str.size()) % str.size()] = vec[(i + 1 + str.size()) % str.size()] + 1;
        }
        if (str[(i + str.size()) % str.size()] == c) {
            ma = max(ma, vec[(i + str.size()) % str.size()]);
        }
    }
    std::cout << ma << std::endl;
}

int main() {
    int t = 0;
    std::cin >> t;
    while (t--) {
        solve();
    }
}
