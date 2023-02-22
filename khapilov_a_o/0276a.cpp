#include <iostream>
int max(int a, int b){
    return (a > b) ? a : b;
}
int min(int a, int b){
    return (a < b) ? a : b;
}
int main()
{
    int n, k;
    std::cin >> n >> k;
    int hapM{-1000000001};
    for(int i = 0; i < n; i++){
        int f, t;
        std::cin >> f >> t;
        hapM = max (hapM, min(f, f - t + k));
    }
    std::cout << hapM;
    return 0;
}