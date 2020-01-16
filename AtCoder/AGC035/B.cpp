#include <iostream>
#include <vector>

using namespace std;

class UnionFind {
public:
    explicit UnionFind(int N) : root(N, -1), size(N, 1) {}
    int getRoot(int u){ return root[u] == -1 ? u : root[u] = getRoot(root[u]); }
    int getSize(int u){ return size[getRoot(u)]; }
    int same(int a, int b){
        return getRoot(a) == getRoot(b);
    }
    int merge(int a, int b){
        int u = getRoot(a);
        int v = getRoot(b);
        if(u != v){
            root[u] = v;
            size[v] += size[u];
        }
    }
private:
    vector<int> root;
    vector<int> size;
};

void dfs(const vector<vector<int>>& g, int pos, int prev, vector<int>& deg){
    for(auto& t : g[pos]){
        if(t == prev) continue;
        dfs(g, t, pos, deg);
    }
    if(prev == -1) return;
    if(deg[pos]%2 == 0){
        cout << prev << " " << pos << endl;
        deg[prev]++;
    } else {
        cout << pos << " " << prev << endl;
        deg[pos]++;
    }
}

int main(){
    int N, M;
    while(cin >> N >> M){
        if(M%2 == 1){
            cout << -1 << endl;
            for(int i=0;i<M;i++){
                int a, b; cin >> a >> b;
            }
            continue;
        }
        vector<vector<int>> g(N+1);
        UnionFind uf(N+1);
        vector<int> deg(N+1, 0);
        for(int i=0;i<M;i++){
            int a, b; cin >> a >> b;
            int u = uf.getRoot(a);
            int v = uf.getRoot(b);
            if(u == v){
                cout << a << " " << b << endl;
                deg[a]++;
            } else {
                uf.merge(a, b);
                g[a].push_back(b);
                g[b].push_back(a);
            }
        }
        dfs(g, 1, -1, deg);
    }
}