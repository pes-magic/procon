#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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

int solve(const vector<vector<int>>& g){
    const int N = g.size();
    if(N==2) return 0;
    if(N==3) return -1;
    FindBridge bridge(g);
    if(bridge.getBridge().empty()) return -1;
    if(bridge.getBridge().size() == 1) return 0;
    UnionFind uf(N);
    for(auto& e : bridge.getEdge()){
        uf.merge(e.first, e.second);
    }
    vector<vector<int>> h(N);
    for(auto& e : bridge.getBridge()){
        int p = uf.getRoot(e.first);
        int q = uf.getRoot(e.second);
        h[p].push_back(q);
        h[q].push_back(p);
    }
    int ones = 0;
    int add = 1;
    for(int i=0;i<N;i++){
        if(h[i].size() != 1) continue;
        ++ones;
        if(h[h[i][0]].size() > 2) add = 0;
    }
    return (ones + add) / 2;
}

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<vector<int>> g(N);
        for(int i=0;i<M;i++){
            int a, b; cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        int res = solve(g);
        if(res >= 0){
            cout << res << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }
}