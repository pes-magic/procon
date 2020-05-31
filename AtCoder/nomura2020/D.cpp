#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

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
    int N; cin >> N;
    UnionFind uf(N);
    vector<int> P(N);
    for(int i=0;i<N;i++){
        cin >> P[i];
        if(P[i] != -1){
            --P[i];
            uf.merge(i, P[i]);
        }
    }
    vector<int> size;
    vector<int> checked(N, 0);
    for(int i=0;i<N;i++){
        if(P[i] == -1){
            int r = uf.getRoot(i);
            checked[r] = 1;
            size.push_back(uf.getSize(r));
        }
    }
    long long res = N;
    for(int i=0;i<N;i++){
        if(uf.getRoot(i) != i) continue;
        if(checked[i]) continue;
        --res;
    }
    for(int i=0;i<size.size();i++) res = (res * (N-1)) % MOD;
    vector<long long> dp(size.size()+1, 0);
    dp[0] = 1;
    for(auto& s : size){
        for(int i=dp.size()-1;i>0;i--){
            dp[i] = (dp[i] + dp[i-1] * s) % MOD;
        }
    }
    long long f = 1;
    for(int i=2;i<dp.size();i++){
        dp[i] = (dp[i] * f) % MOD;
        f = (f * i) % MOD;
    }
    dp[1] = 0;
    for(auto& s : size) dp[1] += s-1;
    long long m = 1;
    for(int i=dp.size()-1;i>0;i--){
        res = (res + MOD - dp[i] * m % MOD) % MOD;
        m = (m * (N-1)) % MOD;
    }
    cout << res << endl;
}