#include <iostream>
#include <vector>

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

int main(){
    int N, Q; cin >> N >> Q;
    UnionFind uf(N);
    for(int i=0;i<Q;i++){
        int t, u, v; cin >> t >> u >> v;
        if(t == 0){
            uf.merge(u, v);
        } else {
            cout << (uf.same(u, v) ? 1 : 0) << endl;
        }
    }
}