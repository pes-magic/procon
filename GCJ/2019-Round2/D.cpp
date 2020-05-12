#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MOD = 1000000007;

class SCC {
public:
    explicit SCC(const vector<vector<int>>& g) : idx(g.size(), -1) {
        const int N = g.size();
        vector<int> order, visit(N, 0);
        for(int i=0;i<N;i++){
            if(!visit[i]) dfs(i, g, order, visit);
        }
        reverse(order.begin(), order.end());
        vector<vector<int>> h(g.size());
        for(int i=0;i<g.size();i++){
            for(auto& t : g[i]) h[t].push_back(i);
        }
        int s = 0;
        for(auto& t : order){
            if(idx[t] != -1) continue;
            compS.push_back(vector<int>());
            dfs2(t, h, s);
            ++s;
        }
        compG.assign(s, vector<int>());
        for(int i=0;i<N;i++){
            for(auto& t : g[i]){
                if(idx[i] != idx[t]) compG[idx[i]].push_back(idx[t]);
            }
        }
    }
    const auto& getGraph() const { return compG; }
    int getCompNum() const { return compG.size(); }
    int getId(int v) const { return idx[v]; }
    const auto& getConnectSet(int id) const { return compS[id]; }
private:
    void dfs(int pos, const vector<vector<int>>& g, vector<int>& order, vector<int>& visit){
        visit[pos] = 1;
        for(auto& t : g[pos]){
            if(visit[t]) continue;
            dfs(t, g, order, visit);
        }
        order.push_back(pos);
    }
    void dfs2(int pos, const vector<vector<int>>& g, int id){
        idx[pos] = id;
        compS[id].push_back(pos);
        for(auto& t : g[pos]){
            if(idx[t] != -1) continue;
            dfs2(t, g, id);
        }
    }
private:
    vector<vector<int>> compG;
    vector<int> idx;
    vector<vector<int>> compS;
};

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

int solve(){
    int N; cin >> N;
    vector<vector<int>> g(N);
    for(int i=0;i<N;i++){
        for(int j=0;j<2;j++){
            int a; cin >> a;
            --a;
            g[i].push_back(a);
        }
    }
    vector<long long> a(N);
    for(auto& t : a) cin >> t;
    SCC scc(g);
    auto order = topologicalSort(scc.getGraph());
    vector<long long> unit(N, 0);
    vector<int> reachable(N, 0);
    reverse(order.begin(), order.end());
    for(auto& id : order){
        if(scc.getId(0) == id){
            int innerEdge = 0;
            for(auto& t : scc.getConnectSet(id)){
                reachable[t] = 1;
                for(auto& dst : g[t]){
                    if(scc.getId(dst) == id) ++innerEdge;
                }
            }
            for(auto& t : scc.getConnectSet(id)){
                unit[t] = (innerEdge <= scc.getConnectSet(id).size() ? 1 : -1);
            }
        } else {
            if(scc.getConnectSet(id).size() == 1){
                int v = scc.getConnectSet(id)[0];
                bool cycle = (g[v][0] == v || g[v][1] == v);
                for(auto& dst : g[v]){
                    if(!reachable[dst]) continue;
                    reachable[v] = 1;
                    if(unit[dst] == -1 || cycle){
                        unit[v] = -1;
                        break;
                    } else {
                        unit[v] = (unit[v] + unit[dst]) % MOD;
                    }
                }
            } else {
                bool reach = false;
                for(auto& v : scc.getConnectSet(id)){
                    for(auto& dst : g[v]){
                        if(!reachable[dst]) continue;
                        reach = true;
                    }
                }
                if(reach){
                    for(auto& v : scc.getConnectSet(id)){
                        reachable[v] = 1;
                        unit[v] = -1;
                    }
                }
            }
        }
    }
    long long res = 0;
    for(int i=0;i<N;i++){
        if(!reachable[i]) continue;
        if(unit[i] == -1 && a[i] > 0) return -1;
        res = (res + unit[i] * a[i]) % MOD;
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        printf("Case #%d: ", t);
        auto res = solve();
        if(res == -1) cout << "UNBOUNDED" << endl;
        else cout << res << endl;
    }
}