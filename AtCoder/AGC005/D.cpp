#include <iostream>
#include <vector>

using namespace std;

const int MOD = 924844033;

vector<int> calc(int n){
    vector<vector<int>> dp(n/2+1, vector<int>(2, 0));
    dp[0][0] = 1;
    for(int i=1;i<n;i++){
        for(int j=dp.size()-2;j>=0;j--){
            dp[j+1][1] = (dp[j+1][1] + dp[j][0]) % MOD;
            dp[j][0] = (dp[j][0] + dp[j][1]) % MOD;
            dp[j][1] = 0;
        }
    }
    vector<int> res(dp.size(), 0);
    for(int i=0;i<dp.size();i++) res[i] = (dp[i][0] + dp[i][1]) % MOD;
    return res;
}

int main(){
    int N, K; cin >> N >> K;
    vector<vector<int>> mem(N+1);
    vector<int> dp(1, 1);
    for(int i=0;i<K;i++){
        int n = (N-1-i)/K+1;
        if(mem[n].empty()) mem[n] = calc(n);
        for(int _=0;_<2;_++){
            vector<int> next(dp.size()+mem[n].size()-1, 0);
            for(int j=0;j<dp.size();j++){
                for(int k=0;k<mem[n].size();k++){
                    next[j+k] += (long long)dp[j] * mem[n][k] % MOD;
                    next[j+k] %= MOD;
                }
            }
            dp = next;
        }
    }
    vector<long long> fact(N+1);
    fact[0] = fact[1] = 1;
    for(int i=2;i<=N;i++) fact[i] = i * fact[i-1] % MOD;
    long long res = 0;
    for(int i=0;i<=N;i++){
        if(i >= dp.size()) break;
        long long add = dp[i] * fact[N-i] % MOD;
        if(i%2 == 0) res = (res + add) % MOD;
        else res = (res + MOD - add) % MOD;
    }
    cout << res << endl;
}