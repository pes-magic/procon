#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>
#include <cstdio>

using namespace std;

const double INF = 1e12;
const double EPS = 1e-9;

template<typename T>
class MaxFlow {
public:
    explicit MaxFlow(int n) : g(n), level(n), iter(n) {}
    struct Edge {
        Edge(int to, T cap, int rev) : to(to), cap(cap), rev(rev) {}
        int to, rev;
        T cap;
    };
    void addEdge(int src, int dst, T cap){
        g[src].emplace_back(dst, cap, g[dst].size());
        g[dst].emplace_back(src, 0, g[src].size()-1);
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
            for(T f;(f=dfs(s, t, INF)) > EPS;res+=f);
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
            if(d > EPS){
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

int main(){
    int N, M; cin >> N >> M;
    vector<int> S(N);
    vector<int> T(M);
    for(auto& t : S) cin >> t;
    for(auto& t : T) cin >> t;
    vector<vector<int>> A(N);
    for(int i=0;i<N;i++){
        int K; cin >> K;
        for(int j=0;j<K;j++){
            int t; cin >> t;
            A[i].push_back(t-1);
        }
    }
    double thr = accumulate(S.begin(), S.end(), 0.0);
    double L = 0.0, R = 10000.0;
    for(int _=0;_<100;_++){
        double mid = 0.5*(L+R);
        MaxFlow<double> mf(N+M+2);
        for(int i=0;i<N;i++) mf.addEdge(0, i+1, S[i]);
        for(int i=0;i<M;i++) mf.addEdge(N+1+i, N+M+1, mid*T[i]);
        for(int i=0;i<N;i++){
            for(auto& t : A[i]){
                mf.addEdge(i+1, N+1+t, INF);
            }
        }
        if(mf.maxFlow(0, N+M+1) < thr*(1-EPS)) L = mid;
        else R = mid;
    }
    printf("%.8lf\n", 0.5*(L+R));
}