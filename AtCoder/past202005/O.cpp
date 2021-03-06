#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template<typename CAP, typename COST>
class MinCostFlow {
public:
    explicit MinCostFlow(int N) : g(N) {}
    void addEdge(int src, int dst, CAP cap, COST cost){
        int r1 = g[src].size();
        int r2 = g[dst].size();
        g[src].emplace_back(src, dst, cap, cost, r2);
        g[dst].emplace_back(dst, src, 0, -cost, r1);
    }
    pair<COST, CAP> solve(int s, int t, CAP maxFlow){
        const int n = g.size();
        pair<COST, CAP> res = make_pair(0, 0);
        vector<COST> h(n, 0);
        while(maxFlow > 0){
            vector<COST> dist(n, INF); dist[s] = 0;
            vector<pair<int, int>> prev(n, make_pair(-1, -1));
            priority_queue<pair<COST, int>, vector<pair<COST, int>>, greater<pair<COST, int>>> qu;
            qu.emplace(0, s);
            while(!qu.empty()){
                auto e = qu.top(); qu.pop();
                if(dist[e.second] < e.first) continue;
                for(int i=0;i<g[e.second].size();i++){
                    auto& p = g[e.second][i];
                    if(p.cap > 0 && dist[p.dst] > dist[p.src] + p.cost + h[p.src] - h[p.dst]){
                        dist[p.dst] = dist[p.src] + p.cost + h[p.src] - h[p.dst];
                        prev[p.dst] = make_pair(p.src, i);
                        qu.emplace(dist[p.dst], p.dst);
                    }
                }
            }
            if(prev[t].first == -1) break;
            CAP f = maxFlow;
            for(int u=t;u!=s;u=prev[u].first) f = min(f, g[prev[u].first][prev[u].second].cap);
            for(int u=t;u!=s;u=prev[u].first){
                auto& p = g[prev[u].first][prev[u].second];
                auto& q = g[p.dst][p.rev];
                res.first += f * p.cost;
                p.cap -= f;
                q.cap += f;
            }
            res.second += f;
            for(int i=0;i<n;i++) h[i] += dist[i];
            maxFlow -= f;
        }
        return res;
    }
private:
    class Edge {
    public:
        explicit Edge(int src, int dst, CAP cap, COST cost, int rev) : src(src), dst(dst), cap(cap), cost(cost), rev(rev) {}
        const int src;
        const int dst;
        CAP cap;
        COST cost;
        const int rev;
    };
private:
    const COST INF = 1LL << 60;
    vector<vector<Edge>> g;
};

int main(){
    int N, M; cin >> N >> M;
    vector<long long> A(N), B(N), R(3);
    for(auto& t : A) cin >> t;
    for(auto& t : B) cin >> t;
    for(auto& t : R) cin >> t;
    MinCostFlow<long long, long long> mcf(6*N+5);
    for(int i=0;i<3;i++) mcf.addEdge(0, i+1, M, 0);
    for(int i=0;i<N;i++){
        long long prev = 0;
        long long v = A[i] * B[i];
        for(int j=0;j<3;j++){
            mcf.addEdge(j+1, 4+3*i+j, 1, -(v%R[j]));
            mcf.addEdge(4+3*N+3*i+j, 6*N+4, 1, v - prev);
            prev = v;
            v *= B[i];
        }
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                mcf.addEdge(4+3*i+j, 4+3*N+3*i+k, 1, 0);
            }
        }
    }
    cout << -mcf.solve(0, 6*N+4, 3*M).first << endl;
}