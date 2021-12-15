#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    const int maxSize = 200001;
    vector<long long> inv(maxSize);
    vector<long long> fact(maxSize);
    vector<long long> factInv(maxSize);
    vector<long long> pow2(maxSize);
    for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
    for(int i=2;i<maxSize;i++){
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
        fact[i] = fact[i-1] * i % MOD;
        factInv[i] = factInv[i-1] * inv[i] % MOD;
    }
    pow2[0] = 1;
    for(int i=1;i<=maxSize;i++) pow2[i] = 2 * pow2[i-1] % MOD;
    auto comb = [&](int n, int r){
        if(n < r || r < 0) return 0LL;
        return fact[n] * factInv[n-r] % MOD * factInv[r] % MOD;
    };
    auto perm = [&](int n, int r){
        if(n < r || r < 0) return 0LL;
        return fact[n] * factInv[n-r] % MOD;
    };
    auto catalan = [&](int n){
        if(n <= 0) return 1LL;
        return fact[2*n] * factInv[n] % MOD * factInv[n+1] % MOD;
    };
    long long N, K;
    while(cin >> N >> K){
        vector<long long> factK(N+1);
        factK[0] = 1;
        for(int i=0;i<N;i++) factK[i+1] = factK[i] * (K-i) % MOD;
        long long res = 0;
        for(int i=1;i<=N;i++){
            long long numChoice = factK[i] * factInv[i] % MOD;
            res += numChoice * comb(N-1, i-1) % MOD * pow2[i-1];
            res %= MOD;
        }
        cout << res << endl;
    }
}