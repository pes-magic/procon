#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

int main(){
    int N, K;
    while(cin >> N >> K){
        if(K%2 == 1){
            cout << 0 << endl;
            continue;
        }
        vector<vector<long long>> dp(N+1, vector<long long>(N*N/2+1, 0));
        dp[0][0] = 1;
        for(int i=0;i<N;i++){
            vector<vector<long long>> next(N+1, vector<long long>(N*N/2+1, 0));
            for(int j=0;j<=N;j++){
                for(int k=0;k<=N*N/2;k++){
                    for(int d=-1;d<=1;d++){
                        if(j+d < 0 || N < j+d) continue;
                        if(k+j+d > N*N/2) continue;
                        next[j+d][k+j+d] += (d == -1 ? j*j : d == 0 ? 2*j+1 : 1) * dp[j][k];
                        next[j+d][k+j+d] %= MOD;
                    }
                }
            }
            dp = next;
        }
        cout << dp[0][K/2] << endl;
    }
}