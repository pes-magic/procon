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
    int N, M; cin >> N >> M;
    vector<long long> a(N), b(N);
    for(auto& t : a) cin >> t;
    for(auto& t : b) cin >> t;
    UnionFind uf(N);
    for(int i=0;i<M;i++){
        int s, t; cin >> s >> t;
        --s; --t;
        uf.merge(s, t);
    }
    vector<long long> sumA(N, 0);
    vector<long long> sumB(N, 0);
    for(int i=0;i<N;i++){
        int r = uf.getRoot(i);
        sumA[r] += a[i];
        sumB[r] += b[i];
    }
    cout << (sumA == sumB ? "Yes" : "No") << endl;
}
