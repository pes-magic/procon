#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

string solve(const string& S, const string& T){
    int n = S.size();
    int m = T.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 100000000));
    vector<vector<pair<int, int>>> prev(n+1, vector<pair<int, int>>(m+1));
    dp[0][0] = 0;
    for(int i=0;i<=S.size();i++){
        for(int j=0;j<=T.size();j++){
            if(i < S.size()){
                if(dp[i+1][j] > dp[i][j] + 1){
                    dp[i+1][j] = dp[i][j] + 1;
                    prev[i+1][j] = make_pair(i, j);
                }
            }
            if(j < T.size()){
                if(dp[i][j+1] > dp[i][j] + 1){
                    dp[i][j+1] = dp[i][j] + 1;
                    prev[i][j+1] = make_pair(i, j);
                }
            }
            if(i < S.size() && j < T.size()){
                if(dp[i+1][j+1] > dp[i][j] + (S[i] == T[j] ? 0 : 1)){
                    dp[i+1][j+1] = dp[i][j] + (S[i] == T[j] ? 0 : 1);
                    prev[i+1][j+1] = make_pair(i, j);
                }
            }
        }
    }
    string res = "";
    int pi = S.size(), pj = T.size();
    while(dp[pi][pj] > dp.back().back()/2){
        auto p = prev[pi][pj];
        if(p.second != pj){
            res = T[p.second] + res;
        }
        pi = p.first;
        pj = p.second;
    }
    return S.substr(0, pi) + res;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        string a, b; cin >> a >> b;
        printf("Case #%d: %s\n", t, solve(a, b).c_str());
    }
}