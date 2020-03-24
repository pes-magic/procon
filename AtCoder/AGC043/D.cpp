#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main(){
    int N, MOD;
    while(cin >> N >> MOD){
        const int maxSize = 3*N+1;
        vector<long long> inv(maxSize);
        vector<long long> fact(maxSize);
        for(int i=0;i<2;i++) inv[i] = fact[i] = 1;
        for(int i=2;i<maxSize;i++){
            inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
            fact[i] = fact[i-1] * i % MOD;
        }
        vector<vector<long long>> dp(maxSize, vector<long long>(4*N+1, 0));
        dp[0][N] = 1;
        for(int i=0;i<3*N;i++){
            for(int j=0;j<=4*N;j++){
                int dj[] = {1, -1, 0};
                for(int k=0;k<3;k++){
                    if(j+dj[k] < 0 || 4*N < j+dj[k]) continue;
                    if(i+k+1 > 3*N) continue;
                    dp[i+k+1][j+dj[k]] += dp[i][j] * inv[i+k+1];
                    dp[i+k+1][j+dj[k]] %= MOD;
                }
            }
        }
        long long res = 0;
        for(int i=N;i<=4*N;i+=3) res = (res + dp[3*N][i]) % MOD;
        cout << (fact[3*N] * res) % MOD << endl;
    }
}