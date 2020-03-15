#include <iostream>

using namespace std;

long long solve(long long H, long long W){
    if(min(H, W) == 1) return 1;
    return H*W/2 + ((H%2 == 1 && W%2 == 1) ? 1 : 0);
}

int main(){
    long long H, W;
    while(cin >> H >> W){
        cout << solve(H, W) << endl;
    }
}