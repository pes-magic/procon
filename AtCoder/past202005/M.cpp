#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    vector<vector<int>> g(N);
    for(int i=0;i<M;i++){
        int a, b; cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> pt;
    int s; cin >> s;
    pt.push_back(s-1);
    int K; cin >> K;
    for(int i=0;i<K;i++){
        cin >> s;
        pt.push_back(s-1);
    }

    vector<vector<int>> d(pt.size(), vector<int>(pt.size()));
    for(int i=0;i<pt.size();i++){
        queue<int> qu; qu.push(pt[i]);
        vector<int> dist(N, 1000000000);
        dist[pt[i]] = 0;
        while(!qu.empty()){
            int t = qu.front(); qu.pop();
            for(auto& v : g[t]){
                if(dist[t] + 1 < dist[v]){
                    dist[v] = dist[t] + 1;
                    qu.push(v);
                }
            }
        }
        for(int j=0;j<pt.size();j++){
            d[i][j] = dist[pt[j]];
        }
    }
    vector<vector<long long>> dp(pt.size(), vector<long long>(1<<pt.size(), 1LL<<60));
    dp[0][1<<0] = 0;
    for(int i=0;i<dp[0].size();i++){
        for(int j=0;j<dp.size();j++){
            for(int k=0;k<dp.size();k++){
                if(i&(1<<k)) continue;
                dp[k][i|(1<<k)] = min(dp[k][i|(1<<k)], dp[j][i] + d[j][k]);
            }
        }
    }
    long long res = (1LL << 60);
    for(int i=0;i<dp.size();i++) res = min(res, dp[i].back());
    cout << res << endl;
}