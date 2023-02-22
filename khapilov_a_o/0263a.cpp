#include <iostream>

int main(){
    int a{0};
    for (int i = 1; i <= 5; i++){
        for (int j = 1; j <= 5; j++){
            std::cin >> a;
            if (a == 1){
                std::cout << abs(3 - i) + abs(3 - j);
                return 0;
            }
        }
    }
    return 0;
}