#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    string S; cin >> S;
    const int N = S.size();
    int K; cin >> K;
    int res = 0;
    vector<vector<vector<int>>> dp(K+1, vector<vector<int>>(N, vector<int>(N, 0)));
    for(int d=N-1;d>=0;d--){
        for(int i=0;i+d<N;i++){
            int j = i+d;
            for(int k=0;k<=K;k++){
                if(k < K && S[i] != S[j]){
                    res = max(res, dp[k][i][j] + 2);
                    if(i+1 < N && j > 0){
                        dp[k+1][i+1][j-1] = max(dp[k+1][i+1][j-1], dp[k][i][j] + 2);
                    }
                }
                if(S[i] == S[j]){
                    res = max(res, dp[k][i][j] + (i==j ? 1 : 2));
                    if(i+1 < N && j > 0){
                        dp[k][i+1][j-1] = max(dp[k][i+1][j-1], dp[k][i][j] + (i==j ? 1 : 2));
                    }
                }
                if(i+1 < N) dp[k][i+1][j] = max(dp[k][i+1][j], dp[k][i][j]);
                if(j > 0) dp[k][i][j-1] = max(dp[k][i][j-1], dp[k][i][j]);
            }
        }
    }
    cout << res << endl;
}