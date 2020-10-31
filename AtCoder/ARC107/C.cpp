#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

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
    int N, K; cin >> N >> K;
    vector<vector<int>> a(N, vector<int>(N));
    for(auto& v : a){
        for(auto& t : v) cin >> t;
    }
    UnionFind row(N), col(N);
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            bool okR = true;
            bool okC = true;
            for(int k=0;k<N;k++){
                if(a[i][k]+a[j][k] > K) okR = false;
                if(a[k][i]+a[k][j] > K) okC = false;
            }
            if(okR) row.merge(i, j);
            if(okC) col.merge(i, j);
        }
    }
    vector<long long> fact(N+1, 1);
    for(int i=2;i<=N;i++) fact[i] = (fact[i-1] * i) % MOD;
    long long res = 1;
    for(int i=0;i<N;i++){
        if(row.getRoot(i) == i) res = (res * fact[row.getSize(i)]) % MOD;
        if(col.getRoot(i) == i) res = (res * fact[col.getSize(i)]) % MOD;
    }
    cout << res << endl;
}