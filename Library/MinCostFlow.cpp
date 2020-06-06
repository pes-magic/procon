// 最小費用流
// verified
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B
// https://atcoder.jp/contests/abc004/tasks/abc004_4
// https://atcoder.jp/contests/past202005/tasks/past202005_o

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
    const COST INF = 1LL << 30;
    vector<vector<Edge>> g;
};