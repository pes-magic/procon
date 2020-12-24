#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <numeric>

using namespace std;

bool check(const vector<vector<pair<int, int>>>& g, const vector<pair<int, int>>& e, const string& color, int start){
    const int N = g.size();
    vector<int> visit(2*N, 0);
    vector<int> pass(color.size(), 0);
    const string nextColor = "rb";
    queue<int> qu; qu.push(start);
    visit[start] = 1;
    while(!qu.empty()){
        int p = qu.front(); qu.pop();
        int colIdx = p%2;
        for(auto& edge : g[p/2]){
            if(!pass[edge.second] && color[edge.second] != nextColor[colIdx]) continue;
            int nx = 2 * edge.first + 1 - colIdx;
            if(!visit[nx]){
                visit[nx] = 1;
                qu.push(nx);
            }
            if(!pass[edge.second] && visit[p/2*2 + 1 - colIdx]){
                nx = 2 * edge.first + colIdx;
                if(!visit[nx]){
                    visit[nx] = 1;
                    qu.push(nx);
                }
            }
            pass[edge.second] = 1;
        }
    }
    return accumulate(pass.begin(), pass.end(), 0) == pass.size();
}

int main(){
    int N, M; cin >> N >> M;
    vector<pair<int, int>> edges(M);
    string color;
    vector<vector<pair<int, int>>> g(N);
    for(int i=0;i<M;i++){
        string c;
        cin >> edges[i].first >> edges[i].second >> c;
        color += c;
        --edges[i].first;
        --edges[i].second;
        g[edges[i].first].emplace_back(edges[i].second, i);
        g[edges[i].second].emplace_back(edges[i].first, i);
    }
    bool ok = false;
    for(int i=0;i<2*N;i++){
        if(check(g, edges, color, i)){
            ok = true;
            break;
        }
    }
    cout << (ok ? "Yes" : "No") << endl;
}