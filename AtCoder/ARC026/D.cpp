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
    bool merge(int a, int b){
        int u = getRoot(a);
        int v = getRoot(b);
        if(u != v){
            root[u] = v;
            size[v] += size[u];
        }
        return u != v;
    }
private:
    vector<int> root;
    vector<int> size;
};

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<int> A(M), B(M), C(M), T(M);
        for(int i=0;i<M;i++) cin >> A[i] >> B[i] >> C[i] >> T[i];
        double L = 0.0, R = 1e6;
        for(int _=0;_<200;_++){
            double mid = 0.5*(L+R);
            vector<pair<double, int>> vp;
            for(int i=0;i<M;i++) vp.emplace_back(C[i]-mid*T[i], i);
            sort(vp.begin(), vp.end());
            UnionFind uf(N);
            double cost = 0.0;
            for(auto& p : vp){
                if(uf.merge(A[p.second], B[p.second]) || p.first < 0){
                    cost += p.first;
                }
            }
            if(cost <= 0.0) R = mid;
            else L = mid;
        }
        printf("%.10lf\n", 0.5*(L+R));
    }
}