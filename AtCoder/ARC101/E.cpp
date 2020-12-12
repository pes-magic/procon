#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

const int maxSize = 5001;
long long inv[maxSize];
long long fact[maxSize];
long long factInv[maxSize];
long long invp2[maxSize];

auto div(int n){
    return fact[n] * factInv[n/2] % MOD * invp2[n/2] % MOD;
};

vector<vector<long long>> solve(const vector<vector<int>>& g, int pos, int prev){
    vector dp(2, vector(2, 0LL));
    dp[0][1] = 1;
    for(auto& t : g[pos]){
        if(t == prev) continue;
        auto child = solve(g, t, pos);
        vector next(2, vector(dp[0].size()+child[0].size()-1, 0LL));
        for(int r1=0;r1<2;r1++){
            for(int c1=1;c1<dp[0].size();c1++){
                for(int r2=0;r2<2;r2++){
                    for(int c2=1;c2<child[0].size();c2++){
                        next[(r1+r2)%2][c1+c2] += dp[r1][c1] * child[r2][c2];
                        next[(r1+r2)%2][c1+c2] %= MOD;
                        if(c2 % 2 == 0){
                            next[(r1+r2+1)%2][c1] += dp[r1][c1] * child[r2][c2] % MOD * div(c2);
                            next[(r1+r2+1)%2][c1] %= MOD;
                        }
                    }
                }

            }
        }
        dp = next;
    }
    return dp;
}

int main(){
    for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
    for(int i=2;i<maxSize;i++){
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
        fact[i] = fact[i-1] * i % MOD;
        factInv[i] = factInv[i-1] * inv[i] % MOD;
    }
    invp2[0] = 1;
    for(int i=1;i<maxSize;i++) invp2[i] = (invp2[i-1] * inv[2]) % MOD;
    int N; cin >> N;
    vector<vector<int>> g(N);
    for(int i=0;i<N-1;i++){
        int a, b; cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    auto dp = solve(g, 0, -1);
    long long res = 0;
    for(int i=0;i<2;i++){
        for(int j=2;j<dp[i].size();j+=2){
            auto dif = dp[i][j] * div(j) % MOD;
            if(i == 1) dif = MOD - dif;
            res = (res + dif) % MOD;
        }
    }
    cout << res << endl;
}
