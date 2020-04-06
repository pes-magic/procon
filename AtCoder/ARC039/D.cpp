#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

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

class FindBridge {
public:
    explicit FindBridge(const vector<vector<int>>& g) : ord(g.size(), -1), pre(g.size(), -1) {
        int curOrder = 0;
        search_(g, 0, -1, curOrder);
        auto reorder = [](vector<pair<int, int>>& v){
            for(auto& p : v){
                if(p.first > p.second) swap(p.first, p.second);
            }
            sort(v.begin(), v.end());
        };
        reorder(bridge);
        reorder(edge);
    }
private:
    void search_(const vector<vector<int>>& g, int pos, int prev, int& curOrder){
        ord[pos] = pre[pos] = curOrder;
        ++curOrder;
        for(auto& e : g[pos]){
            if(e == prev) continue;
            if(ord[e] == -1) search_(g, e, pos, curOrder);
            if(ord[pos] < pre[e]){
                bridge.emplace_back(pos, e);
            } else {
                edge.emplace_back(pos, e);
            }
            pre[pos] = min(pre[pos], pre[e]);
        }
    }
public:
    const vector<pair<int, int>> getBridge() const { return bridge; }
    const vector<pair<int, int>> getEdge() const { return edge; }
private:
    vector<int> ord;
    vector<int> pre;
    vector<pair<int, int>> bridge;
    vector<pair<int, int>> edge;
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

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<vector<int>> g(N);
        for(int i=0;i<M;i++){
            int X, Y; cin >> X >> Y;
            --X; --Y;
            g[X].push_back(Y);
            g[Y].push_back(X);
        }
        FindBridge fb(g);
        UnionFind uf(N);
        for(auto& e : fb.getEdge()) uf.merge(e.first, e.second);
        map<int, int> treeIdx;
        int cur = 0;
        for(int i=0;i<N;i++){
            int p = uf.getRoot(i);
            if(treeIdx.count(p)) continue;
            treeIdx[p] = cur;
            ++cur;
        }
        vector<vector<int>> tree(cur);
        for(auto& e : fb.getBridge()){
            int p = treeIdx[uf.getRoot(e.first)];
            int q = treeIdx[uf.getRoot(e.second)];
            tree[p].push_back(q);
            tree[q].push_back(p);
        }
        LCA lca(tree);
        int Q; cin >> Q;
        for(int i=0;i<Q;i++){
            int A, B, C; cin >> A >> B >> C;
            int a = treeIdx[uf.getRoot(A-1)];
            int b = treeIdx[uf.getRoot(B-1)];
            int c = treeIdx[uf.getRoot(C-1)];
            cout << (lca.dist(a, c) == lca.dist(a, b) + lca.dist(b, c) ? "OK" : "NG") << endl;
        }
    }
}