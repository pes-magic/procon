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
    int N, M, K;
    while(cin >> N >> M >> K){
        vector<int> frNum(N, 0);
        vector<vector<int>> block(N);
        UnionFind uf(N);
        for(int i=0;i<M;i++){
            int A, B; cin >> A >> B;
            uf.merge(A-1, B-1);
            ++frNum[A-1];
            ++frNum[B-1];
        }
        for(int i=0;i<K;i++){
            int C, D; cin >> C >> D;
            block[C-1].push_back(D-1);
            block[D-1].push_back(C-1);
        }
        for(int i=0;i<N;i++){
            int res = uf.getSize(i) - frNum[i] - 1;
            for(auto& b : block[i]) if(uf.same(i, b)) --res;
            if(i) cout << " ";
            cout << res;
        }
        cout << endl;
    }
}