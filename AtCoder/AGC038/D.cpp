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

bool solve(const vector<pair<int, int>>& e1, const vector<pair<int, int>>& e2, long long N, long long M){
    if(M == N-1) return e2.empty();
    UnionFind uf(N);
    auto groupNum = N;
    for(auto& e : e1){
        if(uf.merge(e.first, e.second)) --groupNum;
    }
    if(groupNum <= 2) return M == N-1 && e2.empty();
    for(auto& e : e2){
        if(uf.same(e.first, e.second)) return false;
    }
    return M <= N - groupNum + groupNum*(groupNum-1)/2;
}

int main(){
    long long N, M, Q; cin >> N >> M >> Q;
    vector<pair<int, int>> e1;
    vector<pair<int, int>> e2;
    for(int i=0;i<Q;i++){
        int A, B, C; cin >> A >> B >> C;
        if(C == 0){
            e1.emplace_back(A, B);
        } else {
            e2.emplace_back(A, B);
        }
    }
    cout << (solve(e1, e2, N, M) ? "Yes" : "No") << endl;
}