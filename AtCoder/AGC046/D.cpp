#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 998244353;

int main(){
    string S; cin >> S;
    const int N = S.size();
    vector state(N+1, vector(N+1, vector(N+1, 0)));
    state[0][0][0] = 1;
    for(int i=0;i<=N;i++){
        for(int j=N;j>=0;j--){
            for(int k=N;k>=0;k--){
                if(!state[i][j][k]) continue;
                if(i+1 <= N){
                    state[i+1][j][k] = 1;
                    if(S[i] == '0' && k > 0) state[i+1][j+1][k-1] = 1;
                    if(S[i] == '1' && j > 0) state[i+1][j-1][k+1] = 1;
                }
                if(i+2 <= N){
                    if(S[i] == '0' || S[i+1] == '0' && j+1 <= N) state[i+2][j+1][k] = 1;
                    if(S[i] == '1' || S[i+1] == '1' && k+1 <= N) state[i+2][j][k+1] = 1;
                }
                if(j > 0) state[i][j-1][k] = 1;
                if(k > 0) state[i][j][k-1] = 1;
            }
        }
    }
    state[N][0][0] = 0;
    vector dp(N+1, vector(N+1, 0));
    dp[0][0] = 1;
    int res = 0;
    for(int i=N;i>=0;i--){
        vector addJ(N+1, vector(N+1, 0));
        vector addK(N+1, vector(N+1, 0));
        for(int j=0;j<N;j++){
            for(int k=0;k<N;k++){
                addJ[j+1][k] = (addJ[j][k] + dp[j][k]) % MOD;
                addK[j][k+1] = (addK[j][k] + dp[j][k]) % MOD;
            }
        }
        for(int j=0;j<=N;j++){
            for(int k=0;k<=N;k++){
                if(S[i-1] == '0'){
                    dp[j][k] = (dp[j][k] + addK[j][k]) % MOD;
                } else {
                    dp[j][k] = (dp[j][k] + addJ[j][k]) % MOD;
                }
                if(state[i][j][k]) res = (res + dp[j][k]) % MOD;
            }
        }
    }
    cout << res << endl;
}