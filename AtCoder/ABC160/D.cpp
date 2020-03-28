#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    int N, X, Y;
    while(cin >> N >> X >> Y){
        vector<vector<int>> g(N);
        for(int i=0;i<N-1;i++){
            g[i].push_back(i+1);
            g[i+1].push_back(i);
        }
        g[X-1].push_back(Y-1);
        g[Y-1].push_back(X-1);
        vector<int> res(N, 0);
        for(int i=0;i<N;i++){
            vector<int> dist(N, -1);
            dist[i] = 0;
            queue<int> qu; qu.push(i);
            while(!qu.empty()){
                int t = qu.front(); qu.pop();
                for(auto& v : g[t]){
                    if(dist[v] != -1) continue;
                    dist[v] = dist[t] + 1;
                    qu.push(v);
                }
            }
            for(int j=i+1;j<N;j++) ++res[dist[j]];
        }
        for(int i=1;i<N;i++) cout << res[i] << endl;
    }
}