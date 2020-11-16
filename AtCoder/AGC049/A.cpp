#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

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

int main(){
    int N; cin >> N;
    vector<string> vs(N);
    for(auto& s : vs) cin >> s;
    vector<vector<int>> g(N);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++) if(vs[i][j] == '1') g[i].push_back(j);
    }
    SCC scc(g);
    const auto& h = scc.getGraph();
    vector<int> sum(h.size(), 0);
    for(int i=0;i<h.size();i++){
        vector<int> visit(h.size(), 0);
        queue<int> qu;
        visit[i] = 1;
        qu.push(i);
        while(!qu.empty()){
            int pos = qu.front(); qu.pop();
            sum[pos] += scc.getConnectSet(i).size();
            for(auto& t : h[pos]){
                if(visit[t]) continue;
                visit[t] = 1;
                qu.push(t);
            }
        }
    }
    double res = 0.0;
    for(int i=0;i<h.size();i++){
        res += scc.getConnectSet(i).size() / (double)sum[i];
    }
    printf("%.9lf\n", res);
}
