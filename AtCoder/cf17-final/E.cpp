#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

int main(){
    string S; cin >> S;
    int N = S.size();
    vector<vector<int>> g(N/2+1);
    int M; cin >> M;
    for(int i=0;i<M;i++){
        int L, R; cin >> L >> R;
        --L; --R;
        if(L >= N/2){
            L = N-1-L;
            R = N-1-R;
            swap(L, R);
        } else if(R >= N/2){
            if(L == N-1-R) continue;
            if(L < N-1-R){
                R = N-2-R;
            } else {
                --L;
                R = N-1-R;
                swap(L, R);
            }
        }
        R = min(R+1, N/2);
        g[L].push_back(R);
        g[R].push_back(L);
    }
    vector<int> dif(N, 0);
    vector<int> reach(N, -1);
    vector<int> next(N, -1);
    for(int i=0;i<=N/2;i++){
        if(reach[i] != -1) continue;
        reach[i] = i;
        queue<int> qu; qu.push(i);
        while(!qu.empty()){
            int s = qu.front(); qu.pop();
            for(auto& t : g[s]){
                if(reach[t] != -1) continue;
                reach[t] = i;
                qu.push(t);
            }
        }
        int cur = i;
        for(int j=i+1;j<=N/2;j++){
            if(reach[j] != i) continue;
            next[cur] = j;
            cur = j;
        }
    }
    int sum = 0;
    for(int i=0;i<N/2;i++){
        sum += dif[i];
        int rot = (S[N-1-i] - S[i] - sum % 26 + 52) % 26;
        if(rot != 0 && next[i] == -1){
            cout << "NO" << endl;
            return 0;
        }
        sum += rot;
        dif[next[i]] = -rot;
    }
    cout << "YES" << endl;
}