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

int main(){
    int N, M;
    while(cin >> N >> M){
        UnionFind uf(N+1);
        for(int i=0;i<M;i++){
            int x, y, z; cin >> x >> y >> z;
            uf.merge(x, y);
        }
        int res = 0;
        for(int i=1;i<=N;i++) if(uf.getRoot(i) == i) ++res;
        cout << res << endl;
    }
}