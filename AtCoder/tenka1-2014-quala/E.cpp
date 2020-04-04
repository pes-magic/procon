#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <queue>

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
    int H, W;
    while(cin >> H >> W){
        vector<string> c(H);
        for(auto& s : c) cin >> s;
        vector<vector<int>> idx(H, vector<int>(W, -1));
        int cur = 0;
        for(int i=0;i<H;i++){
            for(int j=0;j<W;j++){
                if(idx[i][j] != -1) continue;
                idx[i][j] = cur;
                queue<pair<int, int>> qu; qu.emplace(i, j);
                int dx[] = {-1, 0, 1, 0};
                int dy[] = {0, -1, 0, 1};
                while(!qu.empty()){
                    auto p = qu.front(); qu.pop();
                    for(int d=0;d<4;d++){
                        int nx = p.first + dx[d];
                        int ny = p.second + dy[d];
                        if(nx < 0 || H <= nx || ny < 0 || W <= ny) continue;
                        if(c[p.first][p.second] != c[nx][ny]) continue;
                        if(idx[nx][ny] != -1) continue;
                        idx[nx][ny] = cur;
                        qu.emplace(nx, ny);
                    }
                }
                ++cur;
            }
        }
        vector<vector<int>> height(cur, vector<int>(W, 0));
        for(int i=H-1;i>=0;i--){
            for(int j=0;j<W;j++) height[idx[i][j]][j] = H - i;
        }
        vector<vector<int>> g(cur);
        for(int i=0;i+1<H;i++){
            for(int j=0;j<W;j++){
                if(idx[i][j] != idx[i+1][j]) g[idx[i][j]].push_back(idx[i+1][j]);
            }
        }
        SCC scc(g);
        vector<int> compIdx(cur, -1);
        vector<vector<int>> dp(scc.getCompNum(), vector<int>(W, 0));
        for(int i=0;i<scc.getCompNum();i++){
            for(auto& t : scc.getConnectSet(i)){
                for(int j=0;j<W;j++) dp[i][j] = max(dp[i][j], height[t][j]);
                compIdx[t] = i;
            }
        }
        auto order = topologicalSort(scc.getGraph());
        for(int i=order.size()-1;i>=0;i--){
            for(auto t : scc.getGraph()[order[i]]){
                for(int j=0;j<W;j++) dp[order[i]][j] = max(dp[order[i]][j], dp[t][j]);
            }
        }
        vector<int> sum(scc.getCompNum(), 0);
        for(int i=0;i<sum.size();i++){
            sum[i] = accumulate(dp[i].begin(), dp[i].end(), 0);
        }
        int Q; cin >> Q;
        for(int i=0;i<Q;i++){
            int x, y; cin >> y >> x;
            --x; --y;
            cout << sum[compIdx[idx[x][y]]] << endl;
        }
    }
}