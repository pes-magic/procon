#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class UnionFind {
public:
    explicit UnionFind(int N) : root(N, -1), size(N, 1), edge(N, 0) {}
    int getRoot(int u){ return root[u] == -1 ? u : root[u] = getRoot(root[u]); }
    int getSize(int u){ return size[getRoot(u)]; }
    int same(int a, int b){
        return getRoot(a) == getRoot(b);
    }
    bool merge(int a, int b){
        int u = getRoot(a);
        int v = getRoot(b);
        if(u != v){
            if(edge[u] + edge[v] + 1 > size[u] + size[v]) return false;
            root[u] = v;
            size[v] += size[u];
            edge[v] += edge[u] + 1;
        } else {
            if(edge[u] + 1 > size[u]) return false;
            edge[u]++;
        }
        return true;
    }
private:
    vector<int> root;
    vector<int> size;
    vector<int> edge;
};

int main(){
    int N, H, W;
    while(cin >> N >> H >> W){
        UnionFind uf(H+W);
        long long res = 0;
        vector<pair<int, pair<int, int>>> vp;
        for(int i=0;i<N;i++){
            int r, c, a; cin >> r >> c >> a;
            vp.emplace_back(a, make_pair(r-1, c-1+H));
        }
        sort(vp.rbegin(), vp.rend());
        for(auto& p : vp){
            if(uf.merge(p.second.first, p.second.second)){
                res += p.first;
            }
        }
        cout << res << endl;
    }
}