#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

long long calcInv(long long a){
    return modPow(a, MOD-2);
}

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
    int N, M;
    while(cin >> N >> M){
        vector<pair<int, pair<int, int>>> vp(M);
        for(auto& p : vp) cin >> p.second.first >> p.second.second >> p.first;
        vector<pair<int, pair<int, int>>> use;
        sort(vp.begin(), vp.end());
        UnionFind uf1(N);
        long long res = 0;
        vector<long long> weight;
        for(auto& e : vp){
            if(uf1.merge(e.second.first-1, e.second.second-1)){
                use.push_back(e);
                res += e.first;
                weight.push_back(e.first);
            }
        }
        sort(weight.begin(), weight.end());
        weight.erase(unique(weight.begin(), weight.end()), weight.end());
        if(weight.size() == N-1){
            cout << res << " " << 1 << endl;
            continue;
        }
        long long num = 1;
        for(auto& w : weight){
            UnionFind uf2(N);
            for(auto& e : use){
                if(e.first == w) continue;
                uf2.merge(e.second.first-1, e.second.second-1);
            }
            vector<int> roots;
            for(int i=0;i<N;i++) roots.push_back(uf2.getRoot(i));
            sort(roots.begin(), roots.end());
            roots.erase(unique(roots.begin(), roots.end()), roots.end());
            map<int, int> idx;
            for(int i=0;i<roots.size();i++) idx[roots[i]] = i;
            vector<vector<long long>> M(roots.size(), vector<long long>(roots.size(), 0));
            for(auto& e : vp){
                if(e.first != w) continue;
                int p = idx[uf2.getRoot(e.second.first-1)];
                int q = idx[uf2.getRoot(e.second.second-1)];
                if(p != q){
                    M[p][p]++;
                    M[q][q]++;
                    M[p][q] = (M[p][q] + MOD - 1) % MOD;
                    M[q][p] = (M[q][p] + MOD - 1) % MOD;
                }
            }
            for(int i=0;i<M.size();i++){
                if(M[i][i] == 0) continue;
                long long inv = calcInv(M[i][i]);
                for(int j=i+1;j<M.size();j++){
                    if(M[j][i] == 0) continue;
                    long long mul = (M[j][i] * inv) % MOD;
                    for(int k=i;k<M.size();k++){
                        M[j][k] = (M[j][k] + MOD - M[i][k] * mul % MOD) % MOD;
                    }
                }
            }
            for(int i=0;i<M.size()-1;i++) num = (num * M[i][i]) % MOD;
        }
        cout << res << " " << num << endl;
    }
}