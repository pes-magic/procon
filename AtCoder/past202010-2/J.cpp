#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    long long AB, AC, BC; cin >> AB >> AC >> BC;
    string S; cin >> S;
    vector<vector<pair<int, long long>>> g(N+3);
    for(int i=0;i<M;i++){
        int a, b, c; cin >> a >> b >> c;
        --a; --b;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }
    for(int i=0;i<N;i++){
        if(S[i] == 'A'){
            g[i].emplace_back(N, 0);
            g[N+1].emplace_back(i, AB);
            g[N+2].emplace_back(i, AC);
        } else if(S[i] == 'B'){
            g[N].emplace_back(i, AB);
            g[i].emplace_back(N+1, 0);
            g[N+2].emplace_back(i, BC);
        } else {
            g[N].emplace_back(i, AC);
            g[N+1].emplace_back(i, BC);
            g[i].emplace_back(N+2, 0);
        }
    }
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> qu;
    qu.emplace(0, 0);
    vector<long long> dist(N+3, 1LL << 60);
    dist[0] = 0;
    while(!qu.empty()){
        auto pr = qu.top(); qu.pop();
        if(dist[pr.second] != pr.first) continue;
        for(auto& nd : g[pr.second]){
            int np = nd.first;
            long long nc = nd.second + pr.first;
            if(nc < dist[np]){
                dist[np] = nc;
                qu.emplace(nc, np);
            }
        }
    }
    cout << dist[N-1] << endl;
}