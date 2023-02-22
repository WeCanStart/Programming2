#include <iostream>
#include <string>

int main() {
    std::string str;
    std::cin >> str;
    for (int i = 0; i < str.size() - 2; i += 1) {
        if (str[i] == 'A' && str[i + 1] == 'B' && str[i + 2] == 'C' ||
            str[i] == 'A' && str[i + 1] == 'C' && str[i + 2] == 'B' ||
            str[i] == 'B' && str[i + 1] == 'A' && str[i + 2] == 'C' ||
            str[i] == 'B' && str[i + 1] == 'C' && str[i + 2] == 'A' ||
            str[i] == 'C' && str[i + 1] == 'A' && str[i + 2] == 'B' ||
            str[i] == 'C' && str[i + 1] == 'B' && str[i + 2] == 'A') {
            std::cout << "YES";
            return 0;
        }
    }
    std::cout << "NO";
    return 0;
}