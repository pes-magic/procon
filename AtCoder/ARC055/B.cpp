#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main(){
    int N, K;
    while(cin >> N >> K){
        vector<vector<double>> dp(N, vector<double>(K+1, 0.0));
        for(int i=N-1;i>=0;i--){
            for(int j=0;j<=K;j++){
                if(j == 0) dp[i][j] = 0.0;
                else if(i+j >= N) dp[i][j] = 1.0;
                else {
                    double best = 1.0/(N-i);
                    double no = (1-best)/(i+1);
                    double less = 1.0 - best - no;
                    dp[i][j] = less * dp[i+1][j] + max(best + no * dp[i+1][j-1], no * dp[i+1][j]);
                }
            }
        }
        printf("%.12lf\n", dp[0][K]);
    }
}