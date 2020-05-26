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

bool solve(){
    long long N, M, Q; cin >> N >> M >> Q;
    UnionFind uf(N);
    vector<pair<int, int>> bi;
    long long sz = N;
    for(int i=0;i<Q;i++){
        int a, b, c; cin >> a >> b >> c;
        if(M == N-1 && c == 1) return false;
        if(c == 0){
            if(uf.merge(a, b)) --sz;
        } else {
            bi.emplace_back(a, b);
        }
    }
    if(M == N-1) return true;
    if(!bi.empty() && sz <= 2) return false;
    for(auto& p : bi){
        if(uf.same(p.first, p.second)) return false;
    }
    return N-sz + sz*(sz-1)/2 >= M;
}

int main(){
    cout << (solve() ? "Yes" : "No") << endl;
}