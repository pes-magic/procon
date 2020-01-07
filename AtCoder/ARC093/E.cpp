#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int MOD = 1000000007;

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

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

int main(){
    int N, M;
    while(cin >> N >> M){
        long long X; cin >> X;
        vector<pair<long long, pair<int, int>>> edges(M);
        for(auto& p : edges){ 
            cin >> p.second.first >> p.second.second >> p.first;
            --p.second.first;
            --p.second.second;
        }
        sort(edges.begin(), edges.end());
        UnionFind uf(N);
        vector<vector<pair<int, long long>>> g(N);
        vector<pair<int, pair<int, int>>> outer;
        long long S = 0;
        for(auto& e : edges){
            if(uf.same(e.second.first, e.second.second)){
                outer.push_back(e);
            } else {
                S += e.first;
                uf.merge(e.second.first, e.second.second);
                g[e.second.first].emplace_back(e.second.second, e.first);
                g[e.second.second].emplace_back(e.second.first, e.first);
            }
        }
        vector<vector<long long>> maxEdge(N, vector<long long>(N, 0));
        for(int i=0;i<N;i++){
            queue<int> qu; qu.push(i);
            while(!qu.empty()){
                int p = qu.front(); qu.pop();
                for(auto& next : g[p]){
                    int np = next.first;
                    if(np == i || maxEdge[i][np]) continue;
                    maxEdge[i][np] = max(maxEdge[i][p], next.second);
                    qu.push(np);
                }
            }
        }
        long long D = X - S;
        int same = 0, upper = 0;
        for(auto& e : outer){
            long long dif = e.first - maxEdge[e.second.first][e.second.second];
            if(dif > D) ++upper;
            if(dif == D) ++same;
        }
        long long res = 0;
        if(D == 0){
            res += (modPow(2, N-1) + MOD - 2) * modPow(2, M-(N-1));
            res %= MOD;
        }
        if(D >= 0) {
            res += 2 * (modPow(2, same) + MOD - 1) * modPow(2, upper); 
            res %= MOD;
        }
        cout << res << endl;
    }
}