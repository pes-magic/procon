#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 998244353;

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

long long calcInv(long long a){
    return modPow(a, MOD-2);
}

int main(){
    int n; cin >> n;
    vector<long long> p2(n+1);
    p2[0] = 1;
    for(int i=1;i<=n;i++) p2[i] = 2*p2[i-1]%MOD;
    vector<long long> res(n, 0);
    res[0] = res[1] = n * p2[n-1] % MOD;
    for(int i=2;i<=n-1-i;i++){
        res[i] = (res[i-1] + (2*i-1) * p2[2*i-3]) % MOD;
    }
    for(int i=n-1;i>n-1-i;i--) res[i] = res[n-1-i];
    auto inv = calcInv(p2[n]);
    for(auto& v : res) cout << (v * inv) % MOD << endl;
}