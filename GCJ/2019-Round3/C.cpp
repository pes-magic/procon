#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

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

vector<string> solve(const vector<string>& M){
    const int w = M[0].size();
    const int h = M.size();
    vector<string> res(h-1, string(w-1, '.'));
    int size = w*h;
    UnionFind uf(size);
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(j+1 < w && M[i][j] == M[i][j+1]){
                if(uf.merge(i*w+j, i*w+j+1)) --size;
            }
            if(i+1 < h && M[i][j] == M[i+1][j]){
                if(uf.merge(i*w+j, i*w+w+j)) --size;
            }
        }
    }
    for(int k=0;k<2;k++){
        char c = 'A' + k;
        for(int i=0;i<h-1;i++){
            for(int j=0;j<w-1;j++){
                if(res[i][j] != '.') continue;
                if(M[i][j] == c && M[i][j] == M[i+1][j+1] && uf.merge(i*w+j, i*w+j+w+1)){
                    --size;
                    res[i][j] = '\\';
                } else if(M[i+1][j] == c && M[i+1][j] == M[i][j+1] && uf.merge(i*w+j+1, i*w+j+w)){
                    --size;
                    res[i][j] = '/';
                }
            }
        }
    }
    if(size != 2) return vector<string>();
    return res;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int R, C; cin >> R >> C;
        vector<string> M(R);
        for(auto& s : M) cin >> s;
        auto res = solve(M);
        printf("Case #%d: %s\n", t, res.empty() ? "IMPOSSIBLE" : "POSSIBLE");
        for(auto& s : res) cout << s << endl;
    }
}