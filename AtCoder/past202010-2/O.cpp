#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    vector<long long> v(N+1, 0);
    for(int i=1;i<=N;i++){
        cin >> v[i];
        v[i] += v[i-1];
    }
    int end = 1;
    vector<vector<int>> q(N+1);
    vector<int> l(M), r(M), c(M);
    for(int i=0;i<M;i++){
        cin >> l[i] >> r[i] >> c[i];
        q[l[i]-1].push_back(i);
    }
    vector<long long> dp(N+1, 0);
    priority_queue<int, vector<int>, function<bool(int, int)>> qu(
        [&](int a, int b){
            long long va = dp[l[a]-1] + v[end] - v[l[a]-1] - c[a];
            long long vb = dp[l[b]-1] + v[end] - v[l[b]-1] - c[b];
            return va < vb;
        }
    );
    for(auto& t : q[0]) qu.push(t);
    for(int i=1;i<=N;i++){
        while(!qu.empty()){
            int p = qu.top();
            if(i <= r[p]) break;
            qu.pop();
        }
        dp[i] = dp[i-1];
        if(!qu.empty()){
            int p = qu.top();
            dp[i] = max(dp[i], dp[l[p]-1] + v[i] - v[l[p]-1] - c[p]);
        }
        end = i+1;
        for(auto& t : q[i]) qu.push(t);
    }
    cout << dp.back() << endl;
}