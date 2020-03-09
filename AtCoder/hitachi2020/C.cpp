#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<vector<int>> g(N);
        for(int i=0;i<N-1;i++){
            int a, b; cin >> a >> b;
            g[a-1].push_back(b-1);
            g[b-1].push_back(a-1);
        }
        vector<int> mark(N, -1);
        mark[0] = 0;
        queue<int> qu; qu.push(0);
        while(!qu.empty()){
            int p = qu.front(); qu.pop();
            for(auto& t : g[p]){
                if(mark[t] != -1) continue;
                mark[t] = 1 - mark[p];
                qu.push(t);
            }
        }
        vector<int> cnt(2, 0);
        vector<vector<int>> d(3);
        vector<int> res(N);
        for(int i=1;i<=N;i++) d[i%3].push_back(i);
        for(int i=0;i<N;i++) cnt[mark[i]]++;
        if(cnt[0] > cnt[1]){
            swap(cnt[0], cnt[1]);
            for(auto& t : mark) t = 1 - t;
        }
        if(cnt[0] <= d[0].size()){
            for(int i=0;i<N;i++){
                if(mark[i] == 0){
                    res[i] = d[0].back();
                    d[0].pop_back();
                }
            }
            for(int i=0;i<N;i++){
                if(mark[i] == 0) continue;
                for(int j=0;j<3;j++){
                    if(d[j].empty()) continue;
                    res[i] = d[j].back();
                    d[j].pop_back();
                    break;
                }
            }
        } else {
            for(int i=0;i<N;i++){
                int f = mark[i] + 1;
                if(d[f].empty()) f = 0;
                res[i] = d[f].back();
                d[f].pop_back();
            }
        }
        cout << res[0];
        for(int i=1;i<N;i++) cout << " " << res[i];
        cout << endl;
    }
}