#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

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
    int N; cin >> N;
    UnionFind uf(N);
    vector<pair<int, int>> a(N);
    for(int i=0;i<N;i++){
        int x, y; cin >> x >> y;
        a[N-x].first = y;
        a[N-x].second = i;
    }
    stack<pair<int, int>> st;
    for(auto& p : a){
        int top = p.first;
        while(!st.empty() && p.first < st.top().first){
            uf.merge(p.second, uf.getRoot(st.top().second));
            top = max(top, st.top().first);
            st.pop();
        }
        st.emplace(top, p.second);
    }
    for(int i=0;i<N;i++) cout << uf.getSize(i) << endl;
}