#include <iostream>
#include <vector>

using namespace std;

pair<int, int> search(const vector<vector<int>>& g, int pos, int prev){
    vector<pair<int, int>> vp;
    for(auto& t : g[pos]){
        if(t == prev) continue;
        vp.emplace_back(search(g, t, pos));
    }
    if(vp.empty()) return make_pair(0, 1);
    if(vp.size() == 1) return vp[0];
    int zero = 0;
    for(auto& p : vp){
        if(p.first == 0) ++zero;
    }
    auto res = make_pair(0, 0);
    for(auto& p : vp){
        res.second += max(1, p.first);
    }
    res.first = res.second;
    if(zero > 0) --res.first;
    return res;
}

int main(){
    int N; cin >> N;
    vector<vector<int>> g(N);
    for(int i=0;i<N-1;i++){
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int start = 0;
    while(g[start].size() != 1) ++start;
    auto res = search(g, start, -1);
    cout << min(res.first+1, res.second) << endl;
}