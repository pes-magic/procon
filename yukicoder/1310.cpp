#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main(){
    int N; cin >> N;
    const int maxSize = 200001;
    vector<long long> inv(maxSize);
    vector<long long> fact(maxSize);
    vector<long long> factInv(maxSize);
    for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
    for(int i=2;i<maxSize;i++){
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
        fact[i] = fact[i-1] * i % MOD;
        factInv[i] = factInv[i-1] * inv[i] % MOD;
    }
    auto comb = [&](int n, int r){
        if(n < r || r < 0) return 0LL;
        return fact[n] * factInv[n-r] % MOD * factInv[r] % MOD;
    };
    vector<long long> p2(maxSize);
    p2[0] = 1;
    for(int i=1;i<maxSize;i++) p2[i] = 2*p2[i-1]%MOD;
    long long res = 0;
    for(int i=0;i<=N;i+=2){
        int E = abs(-N+2*i);
        res += p2[E] * comb(N, i);
        res %= MOD;
    }
    cout << (2*res)%MOD << endl;
}