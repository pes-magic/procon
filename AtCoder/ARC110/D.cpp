#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int MOD = 1000000007;

int main(){
    const int maxSize = 2001*2001+2001;
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
    auto perm = [&](int n, int r){
        if(n < r || r < 0) return 0LL;
        return fact[n] * factInv[n-r] % MOD;
    };
    auto catalan = [&](int n){
        if(n <= 0) return 1LL;
        return fact[2*n] * factInv[n] % MOD * factInv[n+1] % MOD;
    };
    int N, M; cin >> N >> M;
    vector<int> A(N);
    for(auto& t : A) cin >> t;
    int sum = accumulate(A.begin(), A.end(), 0);
    long long res = 1;
    for(int i=1;i<=sum+N;i++){
        res = res * (M+N+1-i) % MOD;
        res = res * inv[i] % MOD;
    }
    cout << res << endl;
}