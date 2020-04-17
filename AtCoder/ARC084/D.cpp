#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    int K;
    while(cin >> K){
        vector<int> dist(K+1, 1<<30);
        dist[K] = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> qu;
        qu.emplace(0, K);
        while(!qu.empty()){
            int pos = qu.top().second; qu.pop();
            for(int i=0;i<10;i++){
                if(pos == K && i == 0) continue;
                int npos = (10 * pos + i) % K;
                int ncost = dist[pos] + i;
                if(dist[npos] > ncost){
                    dist[npos] = ncost;
                    qu.emplace(ncost, npos);
                }
            }
        }
        cout << dist[0] << endl;
    }
}