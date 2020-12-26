#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
#include <set>
#include <queue>

using namespace std;

const int INF = 1000000007;

template<typename T>
class MaxFlow {
public:
    explicit MaxFlow(int n) : g(n), level(n), iter(n) {}
    struct Edge {
        Edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
        int to, rev;
        T cap;
    };
    void addEdge(int src, int dst, T cap, bool order=true){
        g[src].emplace_back(dst, cap, g[dst].size());
        g[dst].emplace_back(src, order?0:cap, g[src].size()-1);
    }
    T maxFlow(int s, int t){
        T res = 0;
        int n = g.size();
        while(true){
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            queue<int> qu; qu.push(s);
            while(!qu.empty()){
                int p = qu.front(); qu.pop();
                for(const Edge& e : g[p]){
                    if(e.cap > 0 && level[e.to] == -1){
                        level[e.to] = level[p]+1;
                        qu.push(e.to);
                    }
                }
            }
            if(level[t] == -1) break;
            fill(iter.begin(), iter.end(), 0);
            for(T f;(f=dfs(s, t, INF)) > 0;res+=f);
        }
        return res;
    }
    const vector<vector<Edge>>& getGraph() const { return g; }
private:
    T dfs(int pos, int dst, T f){
        if(pos == dst) return f;
        for(int& i=iter[pos];i<g[pos].size();++i){
            Edge& e = g[pos][i];
            if(e.cap == 0 || level[e.to] <= level[pos]) continue;
            auto d = dfs(e.to, dst, min(f, e.cap));
            if(d > 0){
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
        return 0;
    }
    vector<vector<Edge>> g;
    vector<int> level;
    vector<int> iter;
};

int mem[1<<15][15][15];
int outCost[1<<15][15];

int calc(int checked, int current, int src, int dst, const vector<vector<pair<int, int>>>& g){
    const int N = g.size();
    int res = 0;
    const int out = ((1<<N)-1)^(checked|current);
    for(int i=0;i<N;i++){
        if(!(current&(1<<i))) continue;
        if(i==dst) continue;
        res += outCost[out][i];
    }
    if(mem[current][src][dst] == -1){
        MaxFlow<int> mf(N+2);
        for(int i=0;i<N;i++){
            if(!(current&(1<<i))) continue;
            for(auto& p : g[i]){
                if(!(current&(1<<p.first))) continue;
                if(i==src && p.first==dst) continue;
                if(i==dst && p.first==src) continue;
                if(i > p.first) continue;
                mf.addEdge(i, p.first, p.second, false);
            }
        }
        mf.addEdge(N, src, INF);
        mf.addEdge(dst, N+1, INF);
        mem[current][src][dst] = mem[current][dst][src] = mf.maxFlow(N, N+1);
    }
    return res + mem[current][src][dst];
}

int main(){
    memset(mem, -1, sizeof(mem));
    memset(outCost, 0, sizeof(outCost));
    int N, M; cin >> N >> M;
    vector<vector<pair<int, int>>> g(N);
    for(int i=0;i<M;i++){
        int a, b, c; cin >> a >> b >> c;
        --a; --b;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<(1<<N);j++){
            for(auto& p : g[i]) if((j&(1<<p.first))) outCost[j][i] += p.second;
        }
    }
    vector<vector<int>> dp(N, vector<int>(1<<N, INF));
    dp[0][1<<0] = 0;
    using Node = pair<int, pair<int, int>>;
    priority_queue<Node, vector<Node>, greater<Node>> qu;
    qu.emplace(0, make_pair(0, 1<<0));
    const int all = (1<<N)-1;
    while(!qu.empty()){
        auto [curCost, pr] = qu.top(); qu.pop();
        auto& [pos, mask] = pr;
        if(pos == N-1 && mask == all) break;
        if(dp[pos][mask] < curCost) continue;
        int subset = all^mask;
        for(int k=subset;k;k=(k-1)&subset){
            for(auto& p : g[pos]){
                if(!(k&(1<<p.first))) continue;
                if(p.first==N-1 && (mask|k) != all) continue;
                if(dp[p.first][mask|k] < curCost) continue;
                int nextCost = curCost + calc(mask, k|(1<<pos), pos, p.first, g);
                if(dp[p.first][mask|k] > nextCost){
                    dp[p.first][mask|k] = nextCost;
                    qu.emplace(nextCost, make_pair(p.first, mask|k));
                }
            }
        }
    }
    cout << dp[N-1][all] << endl;
}