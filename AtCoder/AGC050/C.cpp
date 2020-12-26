#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 998244353;

int main(){
    string S; cin >> S;
    const int N = S.size();
    vector<vector<long long>> dp(20, vector<long long>(N+1, 0));
    int b = 0;
    bool find = false;
    for(int i=0;i<S.size();i++){
        for(int j=0;j<20;j++) dp[j][i+1] = (dp[j][i+1] + dp[j][i]) % MOD;
        if(S[i] == 'S') continue;
        for(int j=1;j<20;j++){
            int src = 2, dst = 1;
            for(int k=0;k<20;k++){
                if(i-dst <= b) break;
                dp[min(j-1, k)][i+1] = (dp[min(j-1, k)][i+1] + dp[j][i-dst] + MOD - dp[j][max(b, i-src)]) % MOD;
                src *= 2;
                dst *= 2;
            }
        }
        if(!find) dp[19][i+1] = (dp[19][i+1] + 1) % MOD;
        if(S[i] == 'B'){ b = i; find = true; }
    }
    long long res = 1;
    int lastForce = -1;
    for(int i=0;i<N;i++){
        if(S[i] == '?') res = 2*res % MOD;
        if(S[i] == 'B') lastForce = i;
    }
    for(auto& s : dp){
        res = (res + MOD - (s[N] + MOD - s[max(0, lastForce)]) % MOD) % MOD;
    }
    if(lastForce == -1) res = (res + MOD - 1) % MOD;
    cout << res << endl;
}
