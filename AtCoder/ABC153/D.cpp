#include <iostream>

using namespace std;

int main(){
    long long H;
    while(cin >> H){
        long long res = 0;
        long long num = 1;
        while(H > 0){
            res += num;
            H = H/2;
            num *= 2;
        }
        cout << res << endl;
    }
}