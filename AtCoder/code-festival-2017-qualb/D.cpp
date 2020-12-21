#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int count(const vector<int>& v){
    vector<vector<int>> dp(v.size()+1, vector<int>(3, 0));
    for(int i=0;i<v.size();i++){
        for(int j=0;j<3;j++){
            dp[i+1][0] = max(dp[i+1][0], dp[i][j]);
            if(i+1 >= v.size()) continue;
            int left = v[i];
            if(j == 1) --left;
            if(j == 2) left = min(left-1, 1);
            if(left <= 0) continue;
            if(i+1 < v.size()) dp[i+2][0] = max(dp[i+2][0], dp[i][j] + max(left, v[i+1]));
            dp[i+1][1] = max(dp[i+1][1], dp[i][j] + left);
            dp[i+1][2] = max(dp[i+1][2], dp[i][j] + max(left, v[i+1]-1));
        }
    }
    // for(int j=0;j<3;j++){
    //     for(int i=0;i<dp.size();i++) cout << dp[i][j] << " "; cout << endl;
    // }
    return *max_element(dp.back().begin(), dp.back().end());
}

int naive(const string& S){
    int N = S.size();
    int start = 0;
    for(int i=0;i<N;i++) if(S[i] == '1') start |= 1 << i;
    vector<int> dist(1<<N, -(1<<20));
    dist[start] = 0;
    int res = 0;
    for(int i=(1<<N)-1;i>=0;i--){
        if(dist[i] < 0) continue;
        res = max(res, dist[i]);
        for(int j=0;j+2<N;j++){
            if((i&(1<<j)) && !(i&(1<<(j+1))) && (i&(1<<(j+2)))){
                int next = (i^(1<<j)^(1<<(j+2)))|(1<<(j+1));
                dist[next] = max(dist[next], dist[i]+1);
            }
        }
    }
    return res;
}

int solve(const string& S){
    int idx = 0;
    int res = 0;
    while(true){
        idx = S.find('1', idx);
        if(idx == string::npos) break;
        vector<int> v;
        while(true){
            int cnt = 0;
            while(idx < S.size() && S[idx] == '1'){
                ++cnt;
                ++idx;
            }
            v.push_back(cnt);
            if(idx+1 >= S.size()) break;
            ++idx;
            if(S[idx] == '0') break;
        }
        res += count(v);
    }
    return res;
}

int main(){
   int N; cin >> N;
    string S; cin >> S;
    cout << solve(S) << endl;
}