#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
    vector<vector<long long>> dp(3*N+1, vector<long long>(N+1, 0));
    dp[3*N][0] = 1;
    for(int i=3*N;i>0;i--){
        for(int j=0;j<=N;j++){
            long long m = 1;
            for(int k=1;k<=3;k++){
                if(i-k < 0) break;
                if(j+k/2 > N) break;
                dp[i-k][j+k/2] += dp[i][j] * m;
                dp[i-k][j+k/2] %= M;
                m = m * (i-k) % M;
            }
        }
    }
    long long res = 0;
    for(int i=0;i<=N;i++) res = (res + dp[0][i]) % M;
    cout << res << endl;
}