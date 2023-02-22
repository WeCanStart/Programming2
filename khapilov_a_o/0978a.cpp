#include <iostream>
#include <vector>

int main() {
    std::vector<int> map(1001, -1), arr = {};
    int n, f(0);
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int num;
        std::cin >> num;
        arr.push_back(num);
        if (map[num] != -1) {
            arr[map[num]] = 0;
            f += 1;
        }
        map[num] = i;
    }
    std::cout << size(arr) - f << std::endl;
    for (int i = 0; i < size(arr); i++) {
        if (arr[i] != 0) std::cout << arr[i] << ' ';
    }
}