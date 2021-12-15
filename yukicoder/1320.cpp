#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1LL << 60;

long long dist(const vector<vector<pair<int, long long>>>& g, int s, int t){
    const int N = g.size();
    vector<long long> dist(N, INF);
    dist[s] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> qu;
    qu.emplace(0, s);
    while(!qu.empty()){
        auto [curCost, pos] = qu.top(); qu.pop();
        for(auto& nd : g[pos]){
            if(pos == s && nd.first == t) continue;
            if(pos == t && nd.first == s) continue;
            if(curCost + nd.second < dist[nd.first]){
                dist[nd.first] = curCost + nd.second;
                qu.emplace(dist[nd.first], nd.first);
            }
        }
    }
    return dist[t];
}

int main(){
    int T;
    while(cin >> T){
        int N, M; cin >> N >> M;
        vector<vector<pair<int, long long>>> g(N);
        for(int i=0;i<M;i++){
            int u, v, w; cin >> u >> v >> w;
            --u; --v;
            g[u].emplace_back(v, w);
            if(T == 0) g[v].emplace_back(u, w);
        }
        long long res = INF;
        for(int i=0;i<N;i++){
            for(auto nd : g[i]){
                res = min(res, nd.second + dist(g, nd.first, i));
            }
        }
        cout << (res < INF ? res : -1) << endl;
    }

}