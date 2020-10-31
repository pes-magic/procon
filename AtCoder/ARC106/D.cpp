#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main(){
    const int maxSize = 301;
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
    int N, K; cin >> N >> K;
    vector<long long> sum(K+1, 0);
    for(int i=0;i<N;i++){
        long long A; cin >> A;
        A %= MOD;
        long long cur = 1;
        for(int j=0;j<=K;j++){
            sum[j] = (sum[j] + cur) % MOD;
            cur = (cur * A) % MOD;
        }
    }
    for(int i=1;i<=K;i++){
        long long res = 0;
        for(int j=0;j<=i-j;j++){
            long long add = sum[j] * sum[i-j] % MOD + MOD - sum[i];
            add = (add * comb(i, j)) % MOD;
            if(j == i-j) add = add * inv[2] % MOD;
            res += add;
        }
        cout << res%MOD << endl;
    }
}