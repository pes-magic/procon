#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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
    int K; cin >> K;
    vector<int> N(K), M(K);
    vector<vector<vector<int>>> g(K);
    vector<int> c(K, 1);
    for(int i=0;i<K;i++){
        cin >> N[i] >> M[i];
        vector<vector<int>> h(N[i]);
        for(int j=0;j<M[i];j++){
            int a, b; cin >> a >> b;
            --a; --b;
            h[a].push_back(b);
            h[b].push_back(a);
        }
        for(auto& t : h) if(t.size() != 2) c[i] = 0;
        if(c[i] == 1){
            UnionFind uf(N[i]);
            vector<int> visit(N[i], 0);
            vector<int> sz;
            for(int j=0;j<N[i];j++){
                if(visit[j]) continue;
                queue<int> qu; qu.push(j);
                while(!qu.empty()){
                    int p = qu.front(); qu.pop();
                    for(auto& t : h[p]){
                        if(visit[t]) continue;
                        uf.merge(j, t);
                        visit[t] = 1;
                        qu.push(t);
                    }
                }
                sz.push_back(uf.getSize(j));
            }
            int mn = *min_element(sz.begin(), sz.end());
            int mx = *max_element(sz.begin(), sz.end());
            if(mn == mx && mn%2 == 1){
                c[i] = mn;
            } else {
                c[i] = 0;
            }


        }
        g[i] = std::move(h);
    }
    for(int i=0;i<K;i++){
        for(int j=0;j<K;j++) cout << (((c[i] == c[j] && c[i] > 0) || (M[i] == 0 && M[j] == 0)) ? 1 : 0);
        cout << endl;
    }
}