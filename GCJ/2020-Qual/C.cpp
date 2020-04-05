#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

string solve(const vector<pair<int, int>>& act){
    const int N = act.size();
    vector<int> order(N);
    for(int i=0;i<N;i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b){ return act[a] < act[b]; });
    vector<vector<int>> dp(N+1, vector<int>(24*60+1, -1));
    vector<vector<int>> prev(N, vector<int>(24*60+1, -1));
    dp[0][0] = 0;
    for(int i=1;i<N;i++){
        const int other = act[order[i-1]].second;
        const int start = act[order[i]].first;
        const int end = act[order[i]].second;
        for(int j=0;j<=24*60;j++){
            if(dp[i-1][j] == -1) continue;
            if(other <= start){ dp[i][j] = dp[i-1][j]; prev[i][j] = j; }
            if(j <= start){ dp[i][other] = 1 - dp[i-1][j]; prev[i][other] = j; }
        }
    }
    string res = string(N, '?');
    int start = -1;
    for(int i=0;i<=24*60;i++) if(dp[N-1][i] != -1) start = i;
    if(start == -1) return "IMPOSSIBLE";
    for(int i=N-1;i>=0;i--){
        res[order[i]] = "CJ"[dp[i][start]];
        start = prev[i][start];
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int caseNum=1;caseNum<=T;caseNum++){
        int N; cin >> N;
        vector<pair<int, int>> act(N);
        for(auto& p : act) cin >> p.first >> p.second;
        printf("Case #%d: %s\n", caseNum, solve(act).c_str());
    }
}