#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    int N, K;
    while(cin >> N >> K){
        int res = 0;
        vector<int> deg(N, 0);
        vector<int> next(N, -1);
        vector<int> dist(N, 0);
        for(int i=0;i<N;i++){
            cin >> next[i];
            --next[i];
            if(i == 0 && next[i]){
                ++res;
                next[i] = 0;
            }
            ++deg[next[i]];
        }
        queue<int> qu;
        for(int i=1;i<N;i++) if(!deg[i]) qu.push(i);
        while(!qu.empty()){
            int p = qu.front(); qu.pop();
            if(!p) break;
            if((next[p] && dist[p] == K-1) || (!p && !next[p])){
                ++res;
            } else {
                dist[next[p]] = max(dist[next[p]], dist[p]+1);
            }
            --deg[next[p]];
            if(!deg[next[p]]) qu.push(next[p]);
        }
        cout << res << endl;
    }
}