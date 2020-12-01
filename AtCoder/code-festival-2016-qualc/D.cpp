#include <iostream>
#include <vector>
#include <string>

using namespace std;

int solve(const string& a, const string& b){
    int N = a.size(), M = b.size();
    vector<vector<int>> cost(N+1, vector<int>(M+1, 0));
    vector<vector<int>> dp(N+1, vector<int>(M+1, 0));
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            cost[i][j] = cost[i-1][j-1] + (a[i-1] == b[j-1] ? 1 : 0);
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + cost[i][j];
        }
    }
    return dp[N][M];
}

int main(){
    int H, W; cin >> H >> W;
    vector<string> vs(W);
    for(int i=0;i<H;i++){
        string s; cin >> s;
        for(int j=0;j<W;j++) vs[j] += s[j];
    }
    int res = 0;
    for(int i=0;i+1<W;i++) res += solve(vs[i], vs[i+1]);
    cout << res << endl;
}