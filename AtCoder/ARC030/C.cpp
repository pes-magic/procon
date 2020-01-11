#include <iostream>
#include <vector>
#include <string>
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

int main(){
    int n, m, k;
    while(cin >> n >> m >> k){
        vector<char> vc(n);
        for(auto& c : vc) cin >> c;
        vector<vector<int>> g(n);
        for(int i=0;i<m;i++){
            int a, b; cin >> a >> b;
            --a; --b;
            g[a].push_back(b);
        }
        SCC scc(g);
        auto order = topologicalSort(scc.getGraph());
        string res = "~";
        vector<vector<string>> dp(order.size(), vector<string>(k+1, ""));
        for(auto& t : order){
            vector<char> s;
            for(auto& v : scc.getConnectSet(t)) s.push_back(vc[v]);
            sort(s.begin(), s.end());
            if(dp[t][k].size() == k) res = min(res, dp[t][k]);
            string add = "";
            for(int i=k;i>=0;i--){
                if(dp[t][i].size() == i){
                    res = min(res, dp[t][i] + add);
                }
                for(auto& next : scc.getGraph()[t]){
                    for(int j=0;j+k-i<=k;j++){
                        if(dp[t][j].size() == j){
                            if(dp[next][j+k-i] == "") dp[next][j+k-i] = dp[t][j] + add;
                            else dp[next][j+k-i] = min(dp[next][j+k-i], dp[t][j] + add); 
                        }
                    }
                }
                if(s.size() <= k-i) break;
                if(i != 0) add += s[k-i];
            }
        }
        cout << (res == "~" ? "-1" : res) << endl;
    }
}