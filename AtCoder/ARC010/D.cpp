#include <iostream>
#include <vector>
#include <algorithm>

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
    int N;
    while(cin >> N){
        vector<pair<long long, long long>> f(N);
        for(auto& p : f) cin >> p.first >> p.second;
        int M; cin >> M;
        vector<pair<long long, long long>> s(M);
        for(auto& p : s) cin >> p.first >> p.second;
        sort(s.begin(), s.end());
        vector<vector<int>> g(N);
        for(int i=0;i<N;i++){
            int start = distance(s.begin(), lower_bound(s.begin(), s.end(), f[i]));
            long long minSq = (1LL << 62);
            for(int j=start;j<s.size();j++){
                auto dx = s[j].first - f[i].first;
                if(dx*dx >= minSq) break;
                auto dy = s[j].second - f[i].second;
                minSq = min(minSq, dx*dx+dy*dy);
            }
            for(int j=start-1;j>=0;j--){
                auto dx = s[j].first - f[i].first;
                if(dx*dx >= minSq) break;
                auto dy = s[j].second - f[i].second;
                minSq = min(minSq, dx*dx+dy*dy);
            }
            for(int j=0;j<N;j++){
                if(i == j) continue;
                auto dx = f[j].first - f[i].first;
                auto dy = f[j].second - f[i].second;
                if(dx*dx+dy*dy < minSq) g[i].push_back(j);
            }        
        }
        SCC scc(g);
        auto& h = scc.getGraph();
        vector<int> in(h.size(), 0);
        for(auto& v : h){
            for(auto& t : v) ++in[t];
        }
        int res = 0;
        for(auto& t : in) if(t == 0) ++res;
        cout << res << endl;
    }
}