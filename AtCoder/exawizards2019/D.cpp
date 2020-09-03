#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

int main(){
    const int maxSize = 100001;
    vector<long long> inv(maxSize);
    vector<long long> fact(maxSize);
    vector<long long> factInv(maxSize);
    for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
    for(int i=2;i<maxSize;i++){
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
        fact[i] = fact[i-1] * i % MOD;
        factInv[i] = factInv[i-1] * inv[i] % MOD;
    }
    int N, X; cin >> N >> X;
    vector<int> S(N);
    for(auto& t : S) cin >> t;
    sort(S.begin(), S.end());
    vector<int> sum(100001, 0);
    for(auto& t : S) sum[t] = 1;
    for(int i=1;i<=100001;i++) sum[i] += sum[i-1];
    vector dp(X+1, vector(N+1, 0LL));
    dp[X][N-sum[X]] = 1;
    for(int i=X;i>=S[0];i--){
        for(int j=N;j>=0;j--){
            if(!dp[i][j]) continue;
            if(j > 0){
                dp[i][j-1] += dp[i][j] * j;
                dp[i][j-1] %= MOD;
            }
            for(int k=0;k<sum[i];k++){
                int dst = i%S[k];
                int add = sum[i] - sum[dst] - 1;
                dp[dst][j+add] += dp[i][j];
                dp[dst][j+add] %= MOD;
            }
        }
    }
    long long res = 0;
    for(int i=1;i<S[0];i++){
        for(int j=0;j<=N;j++){
            res += dp[i][j] * fact[j] % MOD * i % MOD;
            res %= MOD;
        }
    }
    cout << res << endl;
}