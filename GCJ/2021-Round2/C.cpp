#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

vector<int> topologicalSort(const vector<vector<int>>& g){
    vector<int> deg(g.size(), 0);
    for(auto& v : g){
        for(auto& t : v) ++deg[t];
    }
    vector<int> res;
    for(int i=0;i<g.size();i++) if(!deg[i]) res.push_back(i);
    for(int i=0;i<g.size();i++){
        for(auto& t : g[res[i]]){
            --deg[t];
            if(!deg[t]) res.push_back(t);
        }
    }
    return res;
}

const int maxSize = 100001;
long long inv[maxSize];
long long fact[maxSize];
long long factInv[maxSize];

void setup(){
    for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
    for(int i=2;i<maxSize;i++){
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
        fact[i] = fact[i-1] * i % MOD;
        factInv[i] = factInv[i-1] * inv[i] % MOD;
    }
}

long long comb(int n, int r){
    if(n < r || r < 0) return 0LL;
    return fact[n] * factInv[n-r] % MOD * factInv[r] % MOD;
}

int solve(const vector<int>& V){
    vector<vector<int>> g(V.size());
    if(V[0] != 1) return 0;
    stack<int> st;
    st.push(0);
    for(int i=1;i<V.size();i++){
        if(V[i] > st.size()+1) return 0;
        while(V[i] < st.size()){
            int p = st.top(); st.pop();
            g[st.top()].push_back(p);
        }
        if(V[i] == st.size()){
            int p = st.top(); st.pop();
            g[i].push_back(p);
        }
        st.push(i);
    }
    while(st.size() >= 2){
        int p = st.top(); st.pop();
        g[st.top()].push_back(p);
    }
    auto order = topologicalSort(g);
    reverse(order.begin(), order.end());
    vector<pair<int, long long>> dp(V.size(), make_pair(0, 0));
    for(const auto& p : order){
        int size = 0;
        for(auto& c : g[p]){
            size += dp[c].first;
        }
        long long num = 1;
        int rest = size;
        for(auto& c : g[p]){
            num *= dp[c].second;
            num %= MOD;
            num *= comb(rest, dp[c].first);
            num %= MOD;
            rest -= dp[c].first;
        }
        dp[p] = make_pair(size+1, num);
    }
    return dp[order.back()].second;
}

int main(){
    setup();
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N; cin >> N;
        vector<int> V(N);
        for(auto& v : V) cin >> v;
        printf("Case #%d: %d\n", t, solve(V));
    }
}