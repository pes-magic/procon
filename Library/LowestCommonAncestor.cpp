// 最小共通祖先
// Verifyed
// https://atcoder.jp/contests/arc039/tasks/arc039_d

class LCA {
public:
    explicit LCA(const vector<vector<int>>& g) : depth(g.size()), parent(g.size()) {
        setup_(g, 0, -1, 0);
    }
    int get(int p, int q) const {
        if(depth[p] < depth[q]) swap(p, q);
        p = getParent_(p, depth[p] - depth[q]);
        if(p == q) return p;
        for(int i=parent[p].size()-1;i>=0;i--){
            if(i >= parent[p].size()) continue;
            if(parent[p][i] != parent[q][i]){
                p = parent[p][i];
                q = parent[q][i];
            }
        }
        return parent[p][0];
    }
    int dist(int p, int q) const {
        return depth[p] + depth[q] - 2 * depth[get(p, q)];
    }
private:
    void setup_(const vector<vector<int>>& g, int pos, int prev, int d){
        if(prev != -1){
            parent[pos].push_back(prev);
            while(parent[parent[pos].back()].size() >= parent[pos].size()){
                parent[pos].push_back(parent[parent[pos].back()][parent[pos].size()-1]);
            }
        }
        depth[pos] = d;
        for(auto& t : g[pos]){
            if(t == prev) continue;
            setup_(g, t, pos, d+1);
        }
    }
    int getParent_(int pos, int d) const {
        int res = pos;
        for(int i=0;d;i++){
            if(d%2) res = parent[res][i];
            d /= 2;
        }
        return res;
    }
private:
    vector<int> depth;
    vector<vector<int>> parent;
};
