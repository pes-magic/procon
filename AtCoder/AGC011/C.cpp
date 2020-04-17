#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    long long alone = 0, bi = 0, crowd = 0;
    vector<vector<int>> g(N);
    for(int i=0;i<M;i++){
        int a, b; cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> mark(N, -1);
    for(int i=0;i<N;i++){
        if(mark[i] != -1) continue;
        if(g[i].empty()){
            ++alone;
            continue;
        }
        queue<int> qu; qu.push(i);
        mark[i] = 0;
        bool b = true;
        while(!qu.empty()){
            int p = qu.front(); qu.pop();
            for(auto t : g[p]){
                if(mark[t] == -1){
                    mark[t] = 1 - mark[p];
                    qu.push(t);
                } else {
                    if(mark[t] + mark[p] != 1) b = false;
                }
            }
        }
        if(b) ++bi;
        else ++crowd;
    }
    long long res = crowd + 2*bi + 2 * bi * (bi - 1) + 2 * bi * crowd + crowd * (crowd - 1);
    res += (long long)N * N - (N - alone) * (N - alone);
    cout << res << endl;
}