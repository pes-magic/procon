#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main(){
    vector<vector<int>> dp(20, vector<int>(400001, 0));
    dp[1][1] = 1;
    for(int i=1;i<19;i++){
        for(int j=1;j<=400000;j++){
            if(!dp[i][j]) continue;
            for(int k=2;1+j*k<=400000;k++){
                dp[i+1][1+j*k] = 1;
            }
        }
    }
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N; cin >> N;
        int res = 1;
        for(int d=3;d<=N;d++){
            if(N%d != 0) continue;
            for(int i=19;i>res;i--){
                if(dp[i][N/d]) res = i;
            }
        }
        printf("Case #%d: %d\n", t, res);
    }
}