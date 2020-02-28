#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int dfs(vector<vector<pair<int, int>>>& g, int pos, int prev){
    int res = 1;
    for(auto& nd : g[pos]){
        if(nd.first == prev) continue;
        nd.second = dfs(g, nd.first, pos);
        res += nd.second;
    }
    for(auto& nd : g[pos]){
        if(nd.first == prev) nd.second = g.size() - res;
    }
    return res;
}

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
    int N;
    vector<long long> pow2(2000001, 1);
    for(int i=1;i<pow2.size();i++) pow2[i] = 2 * pow2[i-1] % MOD;
    while(cin >> N){
        vector<vector<pair<int, int>>> g(N);
        for(int i=0;i<N-1;i++){
            int a, b; cin >> a >> b;
            --a; --b;
            g[a].emplace_back(b, -1);
            g[b].emplace_back(a, -1);
        }
        dfs(g, 0, -1);
        long long res = 0;
        for(auto& nd : g){
            long long sub = (pow2[N-1] + MOD - 1) % MOD;
            for(auto& e : nd){
                sub = (sub + MOD - pow2[e.second]) % MOD;
                sub = (sub + 1) % MOD;
            }
            res = (res + sub) % MOD;
        }
        res = (res * calcInv(modPow(2, N))) % MOD;
        cout << res << endl;
    }
}