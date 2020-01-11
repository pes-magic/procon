#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solver {
public:
    explicit Solver(int N, int M) : N(N), M(M), root(N, -1), member(N), sizeHist(N), rootHist(N) {
        for(int i=0;i<N;i++){
            member[i].insert(i);
            sizeHist[i].emplace_back(0, 1);
            rootHist[i].emplace_back(0, i);
        }
    }
    int getRoot(int u){ return root[u] == -1 ? u : root[u] = getRoot(root[u]); }
    void merge(int a, int b, int w){
        int u = getRoot(a);
        int v = getRoot(b);
        if(u == v) return;
        if(member[u].size() < member[v].size()) swap(u, v);
        root[v] = u;
        member[u].insert(member[v].begin(), member[v].end());
        for(auto& s : member[v]) rootHist[s].emplace_back(w, u);
        sizeHist[u].emplace_back(w, member[u].size());
    }
    int getHistoryRoot(int x, int t){
        auto it = upper_bound(rootHist[x].begin(), rootHist[x].end(), make_pair(t, N));
        --it;
        return it->second;
    }
    int getHistorySize(int x, int t){
        auto it = upper_bound(sizeHist[x].begin(), sizeHist[x].end(), make_pair(t, N));
        --it;
        return it->second;
    }
    int query(int x, int y, int z){
        int L = 0, R = M;
        while(R-L > 1){
            int mid = (L+R)/2;
            int u = getHistoryRoot(x, mid);
            int v = getHistoryRoot(y, mid);
            int s = getHistorySize(u, mid);
            if(u != v) s += getHistorySize(v, mid);
            if(s >= z) R = mid;
            else L = mid;
        }
        return R;
    }
private:
    const int N;
    const int M;
    vector<int> root;
    vector<set<int>> member;
    vector<vector<pair<int,int>>> sizeHist;
    vector<vector<pair<int,int>>> rootHist;
};

int main(){
    int N, M;
    while(cin >> N >> M){
        Solver solver(N+1, M);
        for(int i=0;i<M;i++){
            int a, b; cin >> a >> b;
            solver.merge(a, b, i+1);
        }
        int Q; cin >> Q;
        for(int i=0;i<Q;i++){
            int x, y, z; cin >> x >> y >> z;
            cout << solver.query(x, y, z) << endl;
        }
    }
}