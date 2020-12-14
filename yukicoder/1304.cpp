#include <iostream>
#include <vector>
#include <algorithm>

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
    const int maxSize = 1025;
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
    int N, K, X, Y;
    while(cin >> N >> K >> X >> Y){
        X = min(X, 1023);
        Y = min(Y, 1023);
        vector<int> A(K);
        for(auto& t : A) cin >> t;
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        vector valid(N+1, vector(1024, 0));
        valid[0][0] = 1;
        for(auto& v : A){
            for(int i=N-1;i>=0;i--){
                for(int j=0;j<1024;j++) valid[i+1][j^v] = (valid[i+1][j^v] + valid[i][j]) % MOD;
            }
        }
        vector dp(2, vector(A.size()+1, 0LL));
        dp[1][0] = 1;
        for(int i=0;i<N;i++){
            vector next(2, vector(A.size()+1, 0LL));
            for(int j=0;j<=A.size();j++){
                int n0 = A.size() - j;
                int n1 = j;
                if(n0 > 0){
                    next[1][n1+1] += n0 * dp[1][n1] + (n0-1) * dp[0][n1];
                    next[1][n1+1] %= MOD;
                }
                if(n1 > 0){
                    next[0][n1-1] += n1 * dp[0][n1] + (n1-1) * dp[1][n1];
                    next[0][n1-1] %= MOD;
                }
            }
            dp = next;
        }
        long long res = 0;
        for(int i=0;i<=N;i++){
            if(i >= dp[0].size()) break;
            auto pat = (dp[0][i] + dp[1][i]) % MOD;
            for(int j=X;j<=Y;j++){
                res += pat * valid[i][j] % MOD * calcInv(comb(A.size(), i));
                res %= MOD;
            }
        }
        cout << res << endl;
    }
}