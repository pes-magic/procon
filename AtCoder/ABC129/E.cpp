#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1000000007;

int main(){
    string S;
    while(cin >> S){
        vector<vector<long long>> dp(S.size()+1, vector<long long>(2, 0));
        dp[0][0] = 1;
        for(int i=0;i<S.size();i++){
            if(S[i] == '0'){
                dp[i+1][0] = dp[i][0];
                dp[i+1][1] = 3 * dp[i][1] % MOD;
            } else {
                dp[i+1][0] = 2 * dp[i][0] % MOD;
                dp[i+1][1] = (dp[i][0] + 3 * dp[i][1]) % MOD;
            }
        }
        cout << ((dp.back()[0] + dp.back()[1])%MOD) << endl;
    }
}