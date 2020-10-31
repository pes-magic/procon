#include <iostream>

using namespace std;

const int MOD = 998244353;

int main(){
    long long res = 1;
    for(int i=0;i<3;i++){
        long long a; cin >> a;
        res *= (a*(a+1)/2) % MOD;
        res %= MOD;
    }
    cout << res << endl;

}