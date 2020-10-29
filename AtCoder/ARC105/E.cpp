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
    int T; cin >> T;
    for(int t=0;t<T;t++){
        int N, M; cin >> N >> M;
        UnionFind uf(N);
        for(int i=0;i<M;i++){
            int a, b; cin >> a >> b;
            uf.merge(a-1, b-1);
        }
        long long rest = N * (N-1LL) / 2 - M;
        if(N%2 == 1){
            cout << (rest%2 ? "First" : "Second") << endl;
        } else {
            if(uf.getSize(0)%2 != uf.getSize(N-1)%2){
                cout << "First" << endl;
            } else {
                rest -= (uf.getSize(0)%2) * (uf.getSize(N-1)%2);
                cout << (rest%2 ? "First" : "Second") << endl;
            }
        }

    }
}