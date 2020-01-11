#include <iostream>
#include <vector>
#include <algorithm>

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
        vector<int> a(M), b(M);
        for(int i=0;i<M;i++) cin >> a[i] >> b[i];
        int Q; cin >> Q;
        vector<int> x(Q), y(Q), z(Q);
        for(int i=0;i<Q;i++) cin >> x[i] >> y[i] >> z[i];
        vector<int> L(Q, 0), R(Q, M);
        while(true){
            vector<pair<int, int>> test;
            for(int i=0;i<Q;i++){
                if(R[i]-L[i] > 1) test.emplace_back((L[i]+R[i])/2, i);
            }
            if(test.empty()) break;
            sort(test.begin(), test.end());
            UnionFind uf(N+1);
            int idx = 0;
            for(int i=0;i<M;i++){
                uf.merge(a[i], b[i]);
                while(idx < test.size() && test[idx].first == i+1){
                    int d = test[idx].second;
                    int s = uf.getSize(x[d]);
                    if(!uf.same(x[d], y[d])) s += uf.getSize(y[d]);
                    if(s >= z[d]) R[d] = i+1;
                    else L[d] = i+1;
                    ++idx;
                }
            }
        }
        for(auto& res : R) cout << res << endl;
    }
}