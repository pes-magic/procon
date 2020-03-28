#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;
const int maxSize = 200001;
long long inv[maxSize];
long long fact[maxSize];
long long factInv[maxSize];
map<pair<int, int>, pair<long long, long long>> mp;

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

pair<long long, long long> search(const vector<vector<int>>& g, int pos, int prev){
    if(mp.count(make_pair(pos, prev))) return mp[make_pair(pos, prev)];
    if(mp.count(make_pair(pos, -1))){
        auto all = mp[make_pair(pos, -1)];
        auto part = search(g, prev, pos);
        all.first = (all.first * factInv[g.size()-1]) % MOD;
        all.first = (all.first * fact[g.size()-1-part.second]) % MOD;
        all.first = (all.first * fact[part.second]) % MOD;
        all.first = (all.first * calcInv(part.first)) % MOD;
        all.second -= part.second;
        return mp[make_pair(pos, prev)] = all;
    }
    long long res = 1;
    long long allSize = 0;
    for(auto& t : g[pos]){
        if(t == prev) continue;
        auto pr = search(g, t, pos);
        allSize += pr.second;
        res = (res * pr.first) % MOD;
        res = (res * factInv[pr.second]) % MOD;
    }
    res = (res * fact[allSize]) % MOD;
    return mp[make_pair(pos, prev)] = make_pair(res, allSize+1);
}

int main(){
	for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
	for(int i=2;i<maxSize;i++){
		inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		fact[i] = fact[i-1] * i % MOD;
		factInv[i] = factInv[i-1] * inv[i] % MOD;
	}
    int N;
    while(cin >> N){
        vector<vector<int>> g(N);
        for(int i=0;i<N-1;i++){
            int a, b; cin >> a >> b;
            --a; --b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        mp.clear();
        vector<pair<int, int>> vp;
        for(int i=0;i<N;i++) vp.emplace_back(g[i].size(), i);
        sort(vp.rbegin(), vp.rend());
        vector<int> res(N);
        for(auto& p : vp) res[p.second] = search(g, p.second, -1).first;
        for(auto& t : res) cout << t << endl;
    }
}