#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long long pow(long long a, long long p){
    if(p == 0) return 1;
    auto res = pow(a, p/2);
    res = (res*res);
    if(p%2) res = (res*a);
    return res;
}

int bitCount(long long t){
    int res = 0;
    for(auto i=t;i;i&=(i-1)) ++res;
    return res;
}

long long genMask(const vector<vector<pair<int, int>>>& g, int u, int v){
    queue<int> qu; qu.push(u);
    vector<pair<int, int>> prev(g.size(), make_pair(-1, -1));
    prev[u].first = -2;
    while(!qu.empty()){
        int p = qu.front(); qu.pop();
        for(auto& t : g[p]){
            if(prev[t.first].first != -1) continue;
            prev[t.first] = make_pair(p, t.second);
            qu.push(t.first);
        }
    }
    long long res = 0;
    while(u != v){
        res |= 1LL << prev[v].second;
        v = prev[v].first;
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<vector<pair<int, int>>> g(N);
        for(int i=0;i<N-1;i++){
            int a, b; cin >> a >> b;
            --a; --b;
            g[a].emplace_back(b, i);
            g[b].emplace_back(a, i);
        }
        int M; cin >> M;
        vector<long long> m(M);
        for(int i=0;i<M;i++){
            int u, v; cin >> u >> v;
            --u; --v;
            m[i] = genMask(g, u, v);
        }
        vector<long long> cnt(1<<M, 0);
        for(int i=0;i<(1<<M);i++){
            long long mask = 0;
            for(int j=0;j<M;j++){
                if(i&(1<<j)) mask |= m[j];
            }
            cnt[i] = pow(2, N-1-bitCount(mask));
        }
        long long res = 0;
        for(int i=1;i<(1<<M);i++){
            if(bitCount(i)%2 == 1) res += cnt[i];
            else res -= cnt[i];
        }
        cout << pow(2, N-1) - res << endl;
    }
}