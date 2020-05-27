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

void search(const vector<vector<int>>& g, vector<int>& deg, int pos, int prev){
    for(auto& t : g[pos]){
        if(t == prev) continue;
        search(g, deg, t, pos);
    }
    if(prev != -1){
        if(deg[pos]){
            cout << pos << " " << prev << endl;
        } else {
            cout << prev << " " << pos << endl;
            deg[prev] = 1 - deg[prev];
        }
    }
}

int main(){
    int N, M;
    cin >> N >> M;
    UnionFind uf(N+1);
    if(M%2 == 1){
        cout << -1 << endl;
        return 0;
    }
    vector<int> deg(N+1, 0);
    vector<vector<int>> g(N+1);
    for(int i=0;i<M;i++){
        int a, b; cin >> a >> b;
        if(uf.merge(a, b)){
            g[a].push_back(b);
            g[b].push_back(a);
        } else {
            cout << a << " " << b << endl;
            deg[a] = 1 - deg[a];
        }
    }
    search(g, deg, 1, -1);
}