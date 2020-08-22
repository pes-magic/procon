#include <iostream>

using namespace std;

long long modPow(long long a, long long p, long long mod){
    if(p == 0) return 1;
    auto res = modPow(a, p/2, mod);
    res = (res*res)%mod;
    if(p%2) res = (res*a)%mod;
    return res;
}

long long calcInv(long long a, long long mod){
    return modPow(a, mod-2, mod);
}

int main(){
    const int MOD = 1000000007;
    int p, k;
    while(cin >> p >> k){
        int m = modPow(10, p-1, p);
        int d = (modPow(10, p-1, MOD) + MOD - m) * calcInv(p, MOD) % MOD;
        if(k < m) d = (d+1)%MOD;
        cout << d << endl;
    }
}