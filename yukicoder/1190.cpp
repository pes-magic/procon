#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1LL << 40;

vector<long long> getDist(const vector<vector<int>>& g, int start){
    queue<int> qu; qu.emplace(start);
    vector<long long> dist(g.size(), INF);
    dist[start] = 0;
    while(!qu.empty()){
        int p = qu.front(); qu.pop();
        for(auto& t : g[p]){
            if(dist[t] <= dist[p]+1) continue;
            dist[t] = dist[p] + 1;
            qu.push(t);
        }
    }
    return dist;
}

int main(){
    int N, M, P;
    while(cin >> N >> M >> P){
        int S, G; cin >> S >> G;
        --S; --G;
        vector<vector<int>> g(2*N);
        for(int i=0;i<M;i++){
            int u, v; cin >> u >> v;
            --u; --v;
            g[u].push_back(N+v);
            g[v].push_back(N+u);
            g[N+u].push_back(v);
            g[N+v].push_back(u);
        }
        auto s = getDist(g, S);
        auto e = getDist(g, G);
        vector<int> res;
        for(int i=0;i<N;i++){
            bool ok = false;
            for(int j=0;j<2;j++){
                if(s[i+j*N] + e[i+(P%2+j)%2*N] <= P) ok = true;
            }
            if(ok) res.push_back(i+1);
        }
        if(res.empty()){
            cout << -1 << endl;
        } else {
            cout << res.size() << endl;
            for(auto& t : res) cout << t << endl;
        }
    }
}