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

int main(){
    int N, M;
    while(cin >> N >> M){
        UnionFind uf(N+1);
        vector<pair<int, pair<int,int>>> edge;
        for(int i=1;i<=N;i++){
            int c; cin >> c;
            edge.emplace_back(c, make_pair(0, i));
        }
        for(int i=0;i<M;i++){
            int a, b, r; cin >> a >> b >> r;
            edge.emplace_back(r, make_pair(a, b));
        }
        sort(edge.begin(), edge.end());
        long long res = 0;
        for(auto& e : edge){
            if(uf.merge(e.second.first, e.second.second)){
                res += e.first;
            }
        }
        cout << res << endl;
    }
}