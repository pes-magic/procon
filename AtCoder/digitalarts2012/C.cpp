#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

int main(){
    int N, M, K; cin >> N >> M >> K;
    vector<int> res(N+1, 0);
    vector<vector<int>> tw(N+1);
    vector<map<int, int>> fw(N+1);
    auto calc = [&](int u, int v){
        int t = fw[u][v];
        res[u] += distance(upper_bound(tw[v].begin(), tw[v].end(), t), tw[v].end());
    };
    for(int t=0;t<M;t++){
        string q; cin >> q;
        if(q[0] == 't'){
            int u; cin >> u;
            tw[u].push_back(t);
        } else if(q[0] == 'f'){
            int u, v; cin >> u >> v;
            fw[u][v] = t;
            fw[v][u] = t;
        } else {
            int u, v; cin >> u >> v;
            calc(u, v);
            calc(v, u);
            fw[u].erase(v);
            fw[v].erase(u);
        }
    }
    for(int i=1;i<=N;i++){
        for(auto& p : fw[i]) calc(i, p.first);
    }
    for(int i=1;i<=N;i++) res[i] += tw[i].size();
    sort(res.rbegin(), res.rend());
    cout << res[K-1] << endl;
}