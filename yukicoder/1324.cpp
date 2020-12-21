#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

using namespace std;

template<typename CAP, typename COST>
class MinCostFlow {
public:
    explicit MinCostFlow(int N) : g(N) {}
    void addEdge(int src, int dst, CAP cap, const vector<COST>& cost){
        int r1 = g[src].size();
        int r2 = g[dst].size();
        g[src].emplace_back(src, dst, cap, cost, r2);
        g[dst].emplace_back(dst, src, 0, cost, r1);
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
                    if(p.cap > 0 && dist[p.dst] > dist[p.src] + p.cost() + h[p.src] - h[p.dst]){
                        dist[p.dst] = dist[p.src] + p.cost() + h[p.src] - h[p.dst];
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
                res.first += f * p.cost();
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
        explicit Edge(int src, int dst, CAP cap, const vector<COST>& costVec, int rev) : src(src), dst(dst), cap(cap), costVec(costVec), rev(rev) {}
        const int src;
        const int dst;
        CAP cap;
        const int rev;
        COST cost(){
            if(src < dst && costVec.size() - cap < 0) assert(false);
            if(src > dst && cap - 1 < 0) assert(false);
            return src < dst ? costVec[costVec.size()-cap] : -costVec[cap-1];
        }
    private:
        vector<COST> costVec;
    };
private:
    const COST INF = 1LL << 30;
    vector<vector<Edge>> g;
};

int main(){
    int N, K;
    while(cin >> N >> K){
        vector<int> A(N), B(N);
        vector P(N, vector(N, 0));
        for(auto& t : A) cin >> t;
        for(auto& t : B) cin >> t;
        int base = 0;
        for(auto& v : P){
            for(auto& t : v){
                cin >> t;
                base += t*t;
            }
        }
        MinCostFlow<int, int> mcf(2*N+2);
        for(int i=0;i<N;i++){
            if(A[i] > 0){
                vector<int> v(A[i], 0);
                mcf.addEdge(0, i+1, A[i], v);
            }
        }
        for(int i=0;i<N;i++){
            if(B[i] > 0){
                vector<int> v(B[i], 0);
                mcf.addEdge(N+1+i, 2*N+1, B[i], v);
            }
        }
        const int THR = 40000;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                vector<int> v(200);
                for(int k=0;k<200;k++){
                    int c1 = P[i][j] - k;
                    int c2 = P[i][j] - (k+1);
                    v[k] = c2*c2 - c1*c1 + THR;
                }
                mcf.addEdge(i+1, N+j+1, 200, v);
            }
        }
        for(int i=0;i<K;i++){
            base += mcf.solve(0, 2*N+1, 1).first - THR;
        }
        cout << base << endl;
    }
}