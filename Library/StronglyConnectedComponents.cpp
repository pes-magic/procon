// 強連結成分分解
// Verifyed
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C
// https://atcoder.jp/contests/arc030/tasks/arc030_3

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