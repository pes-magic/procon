#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main(){
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

    int N, K;
    while(cin >> N >> K){
        vector<int> cnt(1024, 0);
        for(int i=0;i<N;i++){
            int a; cin >> a;
            cnt[a]++;
        }
        vector<vector<long long>> dp(11, vector<long long>(1024, 0));
        dp[0][0] = 1;
        for(int k=1;k<1024;k++){
            for(int i=9;i>=0;i--){
                for(int j=0;j<1024;j++){
                    if(j&k) continue;
                    dp[i+1][j|k] = (dp[i+1][j|k] + cnt[k] * dp[i][j]) % MOD;
                }
            }
        }
        long long res = 0;
        for(int i=0;i<=10;i++){
            if(i > K) break;
            for(auto& t : dp[i]){
                res = (res + t * comb(cnt[0], K-i)) % MOD;
            }
        }
        cout << res << endl;
    }
}