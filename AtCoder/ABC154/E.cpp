#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    string N;
    int K;
    while(cin >> N >> K){
        vector<vector<long long>> dp(2, vector<long long>(K+2, 0));
        dp[1][0] = 1;
        for(auto& c : N){
            int v = c - '0';
            vector<vector<long long>> next(2, vector<long long>(K+2, 0));            
            for(int i=0;i<=K;i++){
                next[0][i] += dp[0][i];
                next[0][i+1] += 9 * dp[0][i];
                if(v == 0){
                    next[1][i] += dp[1][i];
                } else {
                    next[1][i+1] += dp[1][i];
                    next[0][i+1] += (v-1) * dp[1][i];
                    next[0][i] += dp[1][i];
                }
            }
            dp = next;
        }
        cout << dp[0][K] + dp[1][K] << endl;
    }
}