#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

const long long INF = 1LL << 60;

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

int main(){
    int n, m; cin >> n >> m;
    vector<long long> v(n), h(n);
    for(auto& t : v) cin >> t;
    for(auto& t : h) cin >> t;
    vector<int> a(m), x(m), b(m), y(m);
    vector<vector<int>> thr(n);
    for(int i=0;i<n;i++){
        thr[i].push_back(0);
        thr[i].push_back(v[i]);
    }
    for(int i=0;i<m;i++){
        cin >> a[i] >> x[i] >> b[i] >> y[i];
        thr[a[i]-1].push_back(x[i]);
        thr[b[i]-1].push_back(y[i]);
    }
    map<pair<int, int>, int> mp;
    for(int i=0;i<n;i++){
        sort(thr[i].begin(), thr[i].end());
        thr[i].erase(unique(thr[i].begin(), thr[i].end()), thr[i].end());
        for(auto& t : thr[i]){
            int s = mp.size()+1;
            mp[make_pair(i, t)] = s;
        }
    }
    long long res = 0;
    MaxFlow<long long> mf(mp.size()+2);
    for(int i=0;i<n;i++){
        res += max(0LL, h[i]) * v[i];
        int src = mp[make_pair(i, 0)];
        int dst = mp[make_pair(i, v[i])];
        mf.addEdge(0, src, INF);
        mf.addEdge(dst, mp.size()+1, max(0LL, -h[i]) * v[i]);
        for(int j=0;j+1<thr[i].size();j++){
            if(h[i] > 0){
                mf.addEdge(src+j, src+j+1, (v[i]-(thr[i][j+1]-1)) * h[i]);
            } else {
                mf.addEdge(src+j, src+j+1, -thr[i][j] * h[i]);
            }
            mf.addEdge(src+j+1, src+j, INF);
        }
    }
    for(int i=0;i<m;i++){
        int s = mp[make_pair(a[i]-1, x[i])];
        int t = mp[make_pair(b[i]-1, y[i])];
        mf.addEdge(s, t, INF);
    }
    cout << res - mf.maxFlow(0, mp.size()+1) << endl;
}