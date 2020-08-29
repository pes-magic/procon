#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

template<typename T>
class RangeUpdateQuery {
public:
    explicit RangeUpdateQuery(int n, T def) : N(calcN_(n)) {
        mVal.assign(2*N+1, make_pair(-1, def));
    }
    void update(int l, int r, T value, int ts){
        l = max(0, l);
        r = min(N, r);
        int offset = N;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ mVal[offset+l-1].first = ts; mVal[offset+l-1].second = value; l++; }
            if(r&1){ mVal[offset+r-2].first = ts; mVal[offset+r-2].second = value; }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
    }
    T get(int idx){
        int i = N + idx - 1;
        auto res = mVal[i];
        while(i > 0){
            i = (i-1)/2;
            res = max(mVal[i], res);
        }
        return res.second;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    const int N;
    vector<pair<int,T>> mVal;
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

struct Segment {
    explicit Segment(int begin, int end, int y, int idx, bool pop)
        : begin(begin), end(end), y(y), idx(idx), pop(pop)
    {}
    bool operator < (const Segment& seg) const { return y != seg.y ? y < seg.y : begin < seg.begin; }
    int begin, end;
    int y;
    int idx;
    bool pop;
};

int main(){
    int n; cin >> n;
    vector<int> pos;
    vector<int> x, y, r;
    auto append = [&](int a, int b, int c){
        x.push_back(a+b);
        y.push_back(a-b);
        r.push_back(c);
        pos.push_back(a+b-c);
        pos.push_back(a+b+c);
    };
    for(int i=0;i<n;i++){
        int a, b, c; cin >> a >> b >> c;
        append(a, b, c);
    }
    int m; cin >> m;
    for(int i=0;i<2*m;i++){
        int a, b; cin >> a >> b;
        append(a, b, 0);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    map<int, int> idx;
    for(int i=0;i<pos.size();i++) idx[pos[i]] = i+1;
    vector<Segment> vs;
    for(int i=0;i<x.size();i++){
        int begin = idx[x[i] - r[i]];
        int end = idx[x[i] + r[i]];
        vs.emplace_back(begin, end, y[i] - r[i], i+1, false);
        if(end > begin){
            vs.emplace_back(begin, end, y[i] + r[i], i+1, true);
        }
    }
    sort(vs.begin(), vs.end());
    RangeUpdateQuery<int> seg(pos.size()+1, 0);
    vector<vector<int>> g(x.size()+1);
    for(int i=0;i<vs.size();i++){
        int parent = seg.get(vs[i].begin-1);
        if(!vs[i].pop){
            g[parent].push_back(vs[i].idx);
            g[vs[i].idx].push_back(parent);
        }
        if(vs[i].begin == vs[i].end) continue;
        if(vs[i].pop){
            seg.update(vs[i].begin, vs[i].end, parent, i);
        } else {
            seg.update(vs[i].begin, vs[i].end, vs[i].idx, i);
        }
    }
    LCA lca(g);
    for(int i=0;i<m;i++){
        cout << lca.dist(n+2*i+1, n+2*i+2) - 2 << endl;
    }
}