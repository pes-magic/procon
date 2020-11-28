#include <iostream>
#include <vector>

using namespace std;

void solve(const vector<vector<pair<int, int>>>& g, int pos, vector<int>& res){
    for(auto& p : g[pos]){
        if(res[p.first] != -1) continue;
        if(p.second != res[pos]){
            res[p.first] = p.second;
        } else {
            res[p.first] = (p.second)%g.size()+1;
        }
        solve(g, p.first, res);
    }
}

int main(){
    int N, M; cin >> N >> M;
    vector<vector<pair<int, int>>> g(N);
    for(int i=0;i<M;i++){
        int u, v, c; cin >> u >> v >> c;
        --u; --v;
        g[u].emplace_back(v, c);
        g[v].emplace_back(u, c);
    }
    vector<int> res(N, -1);
    res[0] = 1;
    solve(g, 0, res);
    for(auto& t : res) cout << t << endl;
}