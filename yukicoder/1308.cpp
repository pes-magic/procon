#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    int N, Q;
    long long C;
    while(cin >> N >> Q >> C){
        vector<vector<pair<int, long long>>> g(N);
        for(int i=0;i<N-1;i++){
            int u, v, l; cin >> u >> v >> l;
            g[u-1].emplace_back(v-1, l);
            g[v-1].emplace_back(u-1, l);
        }
        vector<int> x(Q);
        for(auto& t : x){
            cin >> t;
            --t;
        }
        long long res = 0;
        vector<int> seq(1, x[0]);
        vector<long long> cost(1, -C);
        for(int i=0;i+1<Q;i++){
            vector<long long> dist(N, -1);
            vector<int> prev(N, -1);
            dist[x[i+1]] = 0;
            queue<int> qu; qu.push(x[i+1]);
            while(!qu.empty()){
                int p = qu.front(); qu.pop();
                for(auto& nd : g[p]){
                    if(dist[nd.first] != -1) continue;
                    dist[nd.first] = dist[p] + nd.second;
                    prev[nd.first] = p;
                    qu.push(nd.first);
                }
            }
            long long whole = dist[x[i]];
            res += whole;
            int cur = x[i];
            while(true){
                int next = prev[cur];
                if(next == -1) break;
                seq.push_back(next);
                cost.push_back(whole-dist[next]-C);
                cur = next;
            }
        }
        vector<vector<int>> posList(N);
        for(int i=0;i<seq.size();i++){
            posList[seq[i]].push_back(i);
        }
        vector<int> next(seq.size(), -1);
        for(auto& v : posList){
            for(int i=0;i+1<v.size();i++) next[v[i]] = v[i+1];
        }
        vector<long long> dp(seq.size(), 0);
        for(int i=0;i+1<seq.size();i++){
            if(next[i] != -1) dp[next[i]] = max(dp[next[i]], dp[i] + cost[next[i]]);
            dp[i+1] = max(dp[i+1], dp[i]);
        }
        cout << res - dp.back() << endl;
    }
}