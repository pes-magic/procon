#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

class UnionFind {
public:
    explicit UnionFind(int N) : root(N, -1), size(N, 1) {}
    int getRoot(int u){ return root[u] == -1 ? u : root[u] = getRoot(root[u]); }
    int getSize(int u){ return size[getRoot(u)]; }
    bool same(int a, int b){
        return getRoot(a) == getRoot(b);
    }
    bool merge(int a, int b){
        int u = getRoot(a);
        int v = getRoot(b);
        if(u == v) return false;
        root[u] = v;
        size[v] += size[u];
        return true;
    }
private:
    vector<int> root;
    vector<int> size;
};

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
    int getParent_(int pos, int d) const {
        int res = pos;
        for(int i=0;d;i++){
            if(d%2) res = parent[res][i];
            d /= 2;
        }
        return res;
    }
    int getDepth(int v) const { return depth[v]; }
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
private:
    vector<int> depth;
    vector<vector<int>> parent;
};


int main(){
    int N, Q; cin >> N >> Q;
    vector<vector<int>> g(N);
    map<pair<int, int>, int> mp;
    for(int i=0;i<N-1;i++){
        int a, b; cin >> a >> b;
        --a; --b;
        mp[make_pair(a, b)] = i;
        mp[make_pair(b, a)] = i;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    LCA lca(g);
    vector<int> u(Q), v(Q), c(Q);
    for(int i=0;i<Q;i++){
        cin >> u[i] >> v[i] >> c[i];
        --u[i]; --v[i];
    }
    vector<int> res(N-1, 0);
    UnionFind uf(N);
    auto draw = [&](int src, int dst, int color){
        int end = lca.getDepth(dst);
        while(lca.getDepth(src) > end){
            if(uf.getRoot(src) == src){
                int n = lca.getParent_(src, 1);
                res[mp[make_pair(src, n)]] = color;
                uf.merge(src, n);
            }
            src = uf.getRoot(src);
        }
    };
    for(int i=Q-1;i>=0;i--){
        int p = lca.get(u[i], v[i]);
        draw(u[i], p, c[i]);
        draw(v[i], p, c[i]);
    }
    for(auto& t : res) cout << t << endl;
}