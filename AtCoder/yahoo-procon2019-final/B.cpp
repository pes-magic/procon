#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

pair<int, vector<int>> bfs(const vector<vector<int>>& g, int start){
    int last = -1;
    vector<int> d(g.size(), -1);
    queue<int> qu; qu.push(start);
    d[start] = 0;
    while(!qu.empty()){
        int p = qu.front(); qu.pop();
        last = p;
        for(auto& nxt : g[p]){
            if(d[nxt] != -1) continue;
            d[nxt] = d[p] + 1;
            qu.push(nxt);
        }
    }
    return make_pair(last, d);
}

vector<int> dist(const vector<vector<int>>& g){
    auto p1 = bfs(g, 0);
    auto p2 = bfs(g, p1.first);
    auto p3 = bfs(g, p2.first);
    vector<int> res(g.size());
    for(int i=0;i<g.size();i++) res[i] = max(p2.second[i], p3.second[i]);
    sort(res.begin(), res.end());
    return res;
}

vector<vector<int>> readGraph(){
    int N; cin >> N;
    vector<vector<int>> g(N);
    for(int i=0;i<N-1;i++){
        int a, b; cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    return g;
}

int main(){
    const auto g = readGraph();
    const auto h = readGraph();
    const auto d1 = dist(g);
    const auto d2 = dist(h);
    long long diam = max(d1.back(), d2.back());
    long long res = 0;
    long long sum = 0;
    for(auto& t : d2) sum += t;
    int idx = 0;
    for(int i=d1.size()-1;i>=0;i--){
        while(idx < d2.size() && d1[i]+d2[idx]+1 <= diam){
            sum -= d2[idx];
            ++idx;
        }
        res += idx * diam;
        res += sum + (d2.size() - idx) * (1 + d1[i]);
    }
    cout << res << endl;
}