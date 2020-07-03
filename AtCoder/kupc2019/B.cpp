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
    int n, m, W; cin >> n >> m >> W;
    UnionFind uf(n);
    vector<int> w(n), v(n);
    for(int i=0;i<n;i++) cin >> w[i] >> v[i];
    for(int i=0;i<m;i++){
        int a, b; cin >> a >> b;
        --a; --b;
        uf.merge(a, b);
    }
    for(int i=0;i<n;i++){
        int u = uf.getRoot(i);
        if(u != i){
            v[u] += v[i];
            w[u] += w[i];
        }
    }
    vector<int> dp(W+1, 0);
    for(int i=0;i<n;i++){
        if(uf.getRoot(i) != i) continue;
        for(int j=W;j>=w[i];j--){
            dp[j] = max(dp[j], dp[j-w[i]] + v[i]);
        }
    }
    cout << dp.back() << endl;
}