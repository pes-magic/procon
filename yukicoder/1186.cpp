#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<int> dp(M+1, 0);
        dp[0] = 1;
        for(int i=1;i<=M;i++){
            dp[i] = dp[i-1];
            if(N > 1 && i-N >= 0) dp[i] = (dp[i] + dp[i-N]) % MOD;
        }
        cout << dp.back() << endl;
    }
}