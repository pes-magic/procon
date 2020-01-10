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
    int N, Q;
    while(cin >> N >> Q){
        UnionFind uf(2*N);
        for(int i=0;i<Q;i++){
            int w, x, y, z; cin >> w >> x >> y >> z;
            --x; --y; z %= 2;
            if(w == 1){
                uf.merge(2*x, 2*y+z);
                uf.merge(2*x+1, 2*y+1-z);
            } else {
                cout << (uf.same(2*x, 2*y) ? "YES" : "NO") << endl;
            }
        }
    }
}