#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> topologicalSort(const vector<vector<int>>& g){
    vector<int> deg(g.size(), 0);
    for(auto& v : g){
        for(auto& t : v) ++deg[t];
    }
    vector<int> res;
    for(int i=0;i<g.size();i++) if(!deg[i]) res.push_back(i);
    for(int i=0;i<g.size();i++){
        for(auto& t : g[res[i]]){
            --deg[t];
            if(!deg[t]) res.push_back(t);
        }
    }
    return res;
}

pair<int, int> dfs(const vector<vector<int>>& g, vector<int>& visit, int pos, int key){
    for(auto& t : g[pos]){
        if(visit[t] == key) return make_pair(pos, t);
        if(visit[t] != -1) continue;
        visit[t] = key;
        auto pr = dfs(g, visit, t, key);
        if(pr.first >= 0) return pr;
    }
    return make_pair(-1, -1);
}

pair<int, int> findCycleEdge(const vector<vector<int>>& g){
    int N = g.size();
    vector<int> visit(N, -1);
    for(int i=0;i<N;i++){
        if(visit[i] != -1) continue;
        visit[i] = i;
        auto pr = dfs(g, visit, i, i);
        if(pr.first != -1) return pr;
    }
    return make_pair(-1, -1);
}

int main(){
    int N;
    while(cin >> N){
        vector<vector<int>> g(N);
        for(int i=0;i<N;i++){
            int a; cin >> a;
            g[a-1].push_back(i);
        }
        auto cycle = findCycleEdge(g);
        if(cycle.first == -1){
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        for(int i=0;i<g[cycle.first].size();i++){
            if(g[cycle.first][i] == cycle.second){
                g[cycle.first][i] = g[cycle.first].back();
                g[cycle.first].pop_back();
            }
        }
        auto order = topologicalSort(g);
        reverse(order.begin(), order.end());
        bool res = false;
        for(int skip=0;skip<2;skip++){
            vector<int> grandy(N, -1);
            vector<int> check(N+1, 0);
            for(auto& v : order){
                vector<int> print;
                for(auto& t : g[v]){
                    if(!check[grandy[t]]){
                        check[grandy[t]] = 1;
                        print.push_back(grandy[t]);
                    }
                }
                int can_skip = (v == cycle.first ? skip : 0);
                for(int i=0;i<=N;i++){
                    if(!check[i]){
                        if(can_skip > 0){ --can_skip; continue; } 
                        grandy[v] = i; break;
                    }
                }
                for(auto& c : print) check[c] = 0;
            }
            bool ok = true;
            g[cycle.first].push_back(cycle.second);
            for(auto& t : g[cycle.first]){
                check[grandy[t]] = 1;
                if(grandy[t] == grandy[cycle.first]) ok = false;
            }
            g[cycle.first].pop_back();
            for(int i=0;i<grandy[cycle.first];i++) if(!check[i]) ok = false;
            if(ok) res = true;
        }
        cout << (res ? "POSSIBLE" : "IMPOSSIBLE") << endl;
    }
}