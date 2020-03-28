#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SCC {
public:
    explicit SCC(const vector<vector<pair<int, int>>>& g) : idx(g.size(), -1) {
        const int N = g.size();
        vector<int> order, visit(N, 0);
        for(int i=0;i<N;i++){
            if(!visit[i]) dfs(i, g, order, visit);
        }
        reverse(order.begin(), order.end());
        vector<vector<pair<int, int>>> h(g.size());
        for(int i=0;i<g.size();i++){
            for(auto& t : g[i]) h[t.first].emplace_back(i, t.second);
        }
        int s = 0;
        for(auto& t : order){
            if(idx[t] != -1) continue;
            compS.push_back(vector<int>());
            dfs2(t, h, s);
            ++s;
        }
        compG.assign(s, vector<int>());
        inout.assign(s, vector<int>());
        for(int i=0;i<N;i++){
            for(auto& t : g[i]){
                if(idx[i] != idx[t.first] && t.second){
                    compG[idx[i]].push_back(idx[t.first]);
                    inout[idx[i]].push_back(i);
                    inout[idx[t.first]].push_back(t.first);
                }
            }
        }
    }
    const auto& getGraph() const { return compG; }
    const auto& getInout(int group) const { return inout[group]; }
    int getCompNum() const { return compG.size(); }
    int getId(int v) const { return idx[v]; }
    const auto& getConnectSet(int id) const { return compS[id]; }
private:
    void dfs(int pos, const vector<vector<pair<int, int>>>& g, vector<int>& order, vector<int>& visit){
        visit[pos] = 1;
        for(auto& t : g[pos]){
            if(visit[t.first]) continue;
            dfs(t.first, g, order, visit);
        }
        order.push_back(pos);
    }
    void dfs2(int pos, const vector<vector<pair<int, int>>>& g, int id){
        idx[pos] = id;
        compS[id].push_back(pos);
        for(auto& t : g[pos]){
            if(idx[t.first] != -1) continue;
            dfs2(t.first, g, id);
        }
    }
private:
    vector<vector<int>> compG;
    vector<vector<int>> inout;
    vector<int> idx;
    vector<vector<int>> compS;
};

int solve(const vector<vector<pair<int, int>>>& g){
    const int N = g.size();
    SCC scc(g);
    const int sccSize = scc.getCompNum();
    vector<int> inDeg(sccSize, 0);
    for(auto& v : scc.getGraph()){
        for(auto& t : v) ++inDeg[t];
    }
    int pos01 = -1;
    for(int i=0;i<inDeg.size();i++){
        if(inDeg[i] > 1) return 0;
        int outDeg = scc.getGraph()[i].size();
        if(outDeg > 1) return 0;
        if(inDeg[i] == 0 && outDeg == 1){
            if(pos01 != -1) return 0;
            pos01 = i;
        }
    }
    vector<int> hasOdd(sccSize, 0);
    vector<int> deg(N, 0);
    for(int i=0;i<N;i++){
        for(auto& p : g[i]){
            if(scc.getId(i) != scc.getId(p.first)) continue;
            deg[i] += p.second;
            deg[p.first] += p.second;
            if(p.second){
                hasOdd[scc.getId(i)] = 1;
                if(pos01 != -1 && inDeg[scc.getId(i)] == 0 && scc.getGraph()[scc.getId(i)].size() == 0) return 0;
            }
        }
    }
    if(pos01 != -1){
        for(int i=0;i<sccSize;i++){
            if(inDeg[i] == 0 && scc.getGraph()[i].size() == 0) continue;
            vector<int> oddPos;
            for(auto& v : scc.getConnectSet(i)){
                if(deg[v]%2) oddPos.push_back(v);
            }
            if(oddPos.size() > 2) return 0;
            if(oddPos.size() == 2){
                if(scc.getInout(i).size() == 2 && scc.getInout(i)[0] == scc.getInout(i)[1]) return 0;
                for(auto& o : scc.getInout(i)){
                    bool find = false;
                    for(auto& v : oddPos) if(v == o) find = true;
                    if(!find) return 0;
                }
            }
            if(oddPos.empty()){
                if(scc.getInout(i).size() == 2 && scc.getInout(i)[0] != scc.getInout(i)[1]) return 0;
            }
        }
        return 1;
    }
    int res = 0;
    bool checkOdd = false;
    for(int i=0;i<sccSize;i++){
        if(hasOdd[i] && checkOdd) return 0;
        if(hasOdd[i]){ checkOdd = true; res = 0; }
        else if(checkOdd) continue;
        int oddCnt = 0;
        for(auto& v : scc.getConnectSet(i)) if(deg[v]%2) ++oddCnt;
        if(oddCnt > 2) return 0;
        if(oddCnt == 2) res += 2;
        if(oddCnt == 0) res += scc.getConnectSet(i).size();
    }
    return res;
}

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<vector<pair<int, int>>> g(N);
        for(int i=0;i<M;i++){
            int f, t;
            char l;
            cin >> f >> t >> l;
            g[f-1].emplace_back(t-1, l=='E' ? 0 : 1);
        }
        cout << solve(g) << endl;
    }
}