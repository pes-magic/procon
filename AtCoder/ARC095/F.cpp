#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solve(const vector<vector<int>>& g){
    const int N = g.size();
    vector<int> degree;
    for(int i=0;i<N;i++){
        if(g[i].size() == 1) continue;
        vector<int> visit(N, 0);
        visit[i] = 1;
        degree.push_back(g[i].size());
        vector<int> start;
        for(auto& t : g[i]){
            if(g[t].size() != 1) start.push_back(t);
        }
        if(start.size() > 2) return vector<int>();
        for(auto& s : start){
            int cur = s;
            while(cur != -1){
                degree.push_back(g[cur].size());
                visit[cur] = 1;
                int next = -1;
                for(auto& t : g[cur]){
                    if(g[t].size() == 1) continue;
                    if(visit[t]) continue;
                    if(next != -1) return vector<int>();
                    next = t;
                }
                cur = next;
            }
            reverse(degree.begin(), degree.end());
        }
        bool need_rev = false;
        for(int i=0;i<degree.size();i++){
            if(degree[i] == degree[degree.size()-i-1]) continue;
            need_rev = (degree[i] > degree[degree.size()-i-1]);
            break;
        }
        if(need_rev) reverse(degree.begin(), degree.end());
        break;
    }
    vector<int> res(N);
    for(int i=0;i<N;i++) res[i] = i+1;
    int idx = 1;
    for(auto& d : degree){
        for(int i=0;i<d-2;i++){
            swap(res[idx], res[idx+1]);
            ++idx;
        }
        ++idx;
    }
    return res;
}

int main(){
    int n;
    while(cin >> n){
        vector<vector<int>> g(n);
        for(int i=0;i<n-1;i++){
            int u, v; cin >> u >> v;
            --u; --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        auto res = solve(g);
        if(res.empty()){
            cout << -1 << endl;
        } else {
            cout << res[0];
            for(int i=1;i<n;i++) cout << " " << res[i];
            cout << endl;
        }
    }
}