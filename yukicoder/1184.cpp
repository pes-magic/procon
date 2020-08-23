#include <iostream>

using namespace std;

const int MOD = 998244353;

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

int main(){
    long long N, L;
    while(cin >> N >> L){
        long long res = (modPow(2, (N+L-1)/L) + MOD - 1) % MOD;
        cout << res << endl;
    }
}