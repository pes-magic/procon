#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main(){
    const int maxSize = 10000;
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
    int N, X; cin >> N >> X;
    vector<long long> dp(N+1, 0);
    for(int i=1;i<X;i+=2){
        int baseNum = (i+1)/2;
        for(int j=0;j+baseNum<=N;j++){
            long long c = comb(j, X-1-i-j);
            dp[baseNum+j] += c;
            if(2*baseNum+j <= N){
                dp[2*baseNum+j] += MOD - c;
            }
        }
    }
    if(X%2 == 1) dp[(X-1)/2]++;
    for(int i=0;i<=N;i++){
        for(int j=i;j<X-1;j++){
            if(j-i > N) break;
            long long c = comb(i, j-i);
            dp[i] += c;
            if(i+1 <= N) dp[i+1] += MOD-c;
        }
    }
    for(int i=1;i<=N;i++) dp[i] = (dp[i] + dp[i-1]) % MOD;
    long long res = 0;
    for(int i=0;i<=N;i++){
        res += dp[i] * comb(N, i);
        res %= MOD;
    }
    cout << res << endl;
}
