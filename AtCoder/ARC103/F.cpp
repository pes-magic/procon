#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <numeric>

using namespace std;

vector<vector<int>> solve(vector<long long>& D){
    const int N = D.size();
    map<long long, int> idx;
    for(int i=0;i<N;i++) idx[D[i]] = i;
    vector<pair<long long, int>> vp;
    for(int i=0;i<N;i++) vp.emplace_back(D[i], i);
    sort(vp.rbegin(), vp.rend());
    vector<vector<int>> g(N);
    vector<int> size(N, 1);
    for(auto& p : vp){
        if(size[p.second] == N) break;
        auto cur = p.first;
        auto next = cur - N + 2 * size[p.second];
        if(!idx.count(next)) return vector<vector<int>>();
        int dst = idx[next];
        if(dst == p.second) return vector<vector<int>>();
        size[dst] += size[p.second];
        g[dst].push_back(p.second);
        g[p.second].push_back(dst);
    }
    vector<long long> dist(N, -1);
    dist[0] = 0;
    queue<int> qu; qu.push(0);
    while(!qu.empty()){
        int p = qu.front(); qu.pop();
        for(auto& t : g[p]){
            if(dist[t] != -1) continue;
            dist[t] = dist[p] + 1;
            qu.push(t);
        }
    }
    if(accumulate(dist.begin(), dist.end(), 0LL) != D[0]) return vector<vector<int>>();
    return g;
}

int main(){
    int N; cin >> N;
    vector<long long> D(N);
    for(auto& t : D) cin >> t;
    auto g = solve(D);
    if(!g.empty()){
        for(int i=0;i<N;i++){
            for(auto& t : g[i]){
                if(t < i) continue;
                cout << i+1 << " " << t+1 << endl;
            }
        }

    } else {
        cout << -1 << endl;
    }
}