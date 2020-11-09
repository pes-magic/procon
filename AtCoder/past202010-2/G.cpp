#include <iostream>
#include <vector>
#include <string>
#include <queue>

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
    int N, M; cin >> N >> M;
    vector<string> S(N);
    for(auto& s : S) cin >> s;
    int cnt = 0;
    for(auto& s : S){
        for(auto& c : s) if(c == '.') cnt++;
    }
    int res = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(S[i][j] == '.') continue;
            S[i][j] = '.';
            UnionFind uf(N*M);
            for(int ii=0;ii<N;ii++){
                for(int jj=0;jj<M;jj++){
                    if(S[ii][jj] == '#') continue;
                    int dx[] = {0, 1};
                    int dy[] = {1, 0};
                    for(int d=0;d<2;d++){
                        int ni = ii+dx[d];
                        int nj = jj+dy[d];
                        if(ni < 0 || N <= ni || nj < 0 || M <= nj || S[ni][nj] == '#') continue;
                        uf.merge(ii*M+jj, ni*M+nj);
                    }
                }
            }
            if(uf.getSize(i*M+j) == cnt+1) ++res;
            S[i][j] = '#';
        }
    }
    cout << res << endl;
}