#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main(){
    int N, K; cin >> N >> K;
    vector<vector<long long>> dp(N+1, vector<long long>(2*N+1, 0));
    vector<vector<long long>> sum(N+1, vector<long long>(2*N+1, 0));
    dp[0][0] = 1;
    sum[0][0] = 1;
    for(int i=1;i<=N;i++){
        for(int j=2*N;j>0;j--){
            if(2*j <= 2*N) dp[i][j] = sum[i][2*j];
            sum[i][j] = dp[i][j];
            if(j-2 >= 0) sum[i][j] = (sum[i][j] + sum[i-1][j-2]) % MOD;
        }
    }
    cout << dp[N][K] << endl;
}