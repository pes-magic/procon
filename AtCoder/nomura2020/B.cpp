#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    string T; cin >> T;
    vector<vector<int>> dp(T.size(), vector<int>(2, -1));
    vector<vector<int>> prev(T.size(), vector<int>(2, -1));
    if(T[0] == 'P' || T[0] == '?') dp[0][0] = 0;
    if(T[0] == 'D' || T[0] == '?') dp[0][1] = 1;
    for(int i=1;i<T.size();i++){
        if(T[i] == 'P' || T[i] == '?'){
            for(int j=0;j<2;j++){
                if(dp[i][0] < dp[i-1][j]){
                    dp[i][0] = dp[i-1][j];
                    prev[i][0] = j;
                }
            }
        }
        if(T[i] == 'D' || T[i] == '?'){
            for(int j=0;j<2;j++){
                if(dp[i-1][j] != -1 && dp[i][1] < dp[i-1][j] + 2 - j){
                    dp[i][1] = dp[i-1][j] + 2 - j;
                    prev[i][1] = j;
                }
            }
        }
    }
    int p = (dp.back()[0] < dp.back()[1] ? 1 : 0);
    for(int i=T.size()-1;i>=0;i--){
        T[i] = "PD"[p];
        p = prev[i][p];
    }
    cout << T << endl;
}