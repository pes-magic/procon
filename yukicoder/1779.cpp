#include <iostream>
#include <vector>
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

void solve(){
    int N; cin >> N;
    UnionFind uf(N+1);
    for(int i=2;2*i<=N;i++){
        for(int j=2;j*i<=N;j++){
            uf.merge(i, j*i);
        }
    }
    vector<vector<int>> ca(N), cb(N);
    for(int j=1;j<=N;j++){
        int t; cin >> t;
        ca[uf.getRoot(j)-1].push_back(t);
    }
    for(int j=1;j<=N;j++){
        int t; cin >> t;
        cb[uf.getRoot(j)-1].push_back(t);
    }
    for(auto& s : ca) sort(s.begin(), s.end());
    for(auto& s : cb) sort(s.begin(), s.end());
    cout << (ca == cb ? "Yes" : "No") << endl;
}

int main(){
    int T; cin >> T;
    while(T--){
        solve();
    }
}