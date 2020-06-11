#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>

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

int solve(const vector<int>& a, const vector<int>& b){
    const int N = a.size();
    auto ca = a, cb = b;
    int sumA = 0, sumB = 0;
    for(auto& t : a) sumA ^= t;
    for(auto& t : b) sumB ^= t;
    ca.push_back(sumA);
    cb.push_back(sumB);
    sort(ca.begin(), ca.end());
    sort(cb.begin(), cb.end());
    if(ca != cb) return -1;
    ca.erase(unique(ca.begin(), ca.end()), ca.end());
    map<int, int> mp;
    for(int i=0;i<ca.size();i++) mp[ca[i]] = i;
    UnionFind uf(ca.size());
    vector<int> chg(ca.size(), 0);
    int comp = 0;
    int sub = 0;
    int res = 0;
    for(int i=0;i<N;i++){
        if(a[i] != b[i]){
            if(a[i] == sumA) sub = 1;
            int p = mp[a[i]];
            int q = mp[b[i]];
            if(!chg[p]) ++comp;
            if(uf.merge(p, q)) --comp;
            ++res;
            chg[p] = 1;
        }
    }
    return res + comp - sub;
}

int main(){
    int N; cin >> N;
    vector<int> a(N), b(N);
    for(auto& t : a) cin >> t;
    for(auto& t : b) cin >> t;
    cout << solve(a, b) << endl;
}