#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    vector dp(500, vector(100001, 0));
    vector sum(500, vector(100001, 0));
    dp[0][0] = sum[0][0] = 1;
    for(int i=1;i<500;i++){
        int back = i*(i+1)/2;
        for(int j=back;j<=100000;j++){
            dp[i][j] = (dp[i][j-back] + sum[i-1][j-back]) % MOD;
        }
        for(int j=0;j<=100000;j++) sum[i][j] = (dp[i][j] + sum[i-1][j]) % MOD;
    }
    int N, M; cin >> N >> M;
    vector sum2 = sum;
    for(int i=0;i<500;i++){
        for(int j=N+1;j<=100000;j++) sum2[i][j] = (sum2[i][j] + sum2[i][j-N]) % MOD;
    }
    long long res = 0;
    for(int base=0;base<=M;base+=N){
        if(base == M) res += 1;
        if(M-base > 0) res = (res + 2LL * sum[min(499, N-1)][M-base]) % MOD;
    }
    for(int i=1;i<500;i++){
        int rest = min(499, N-1-i);
        if(rest < 0) break;
        for(int j=1;j<M;j++) res = (res + (long long)dp[i][j] * sum2[rest][M-j]) % MOD;
    }
    cout << res << endl;
}
