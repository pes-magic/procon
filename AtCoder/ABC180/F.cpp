#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

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
    int N, M, L; cin >> N >> M >> L;
    vector dp(2, vector(N+1, vector(M+1, 0LL)));
    dp[0][0][0] = 1;
    for(int i=0;i<2;i++){
        for(int j=0;j<=N;j++){
            for(int k=0;k<=M;k++){
                for(int l=1;l<=L;l++){
                    if(j+l > N) break;
                    if(l == 1){
                        dp[i||l==L][j+l][k] += dp[i][j][k];
                        dp[i||l==L][j+l][k] %= MOD;
                    } else {
                        if(k+l-1 <= M){
                            const auto line = dp[i][j][k] * comb(N-j-1, l-1) % MOD * fact[l] % MOD * inv[2] % MOD;
                            dp[i||l==L][j+l][k+l-1] += line;
                            dp[i||l==L][j+l][k+l-1] %= MOD;
                        }
                        if(k+l <= M){
                            const auto loop = dp[i][j][k] * comb(N-j-1, l-1) % MOD * fact[l-1] % MOD;
                            dp[i||l==L][j+l][k+l] += loop * (l==2 ? 1 : inv[2]);
                            dp[i||l==L][j+l][k+l] %= MOD;
                        }
                    }
                }
            }
        }
    }
    cout << dp[1][N][M] << endl;
}