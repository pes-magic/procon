#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    int N, K; cin >> N >> K;
    vector<long long> dp(1, 1);
    for(int i=N;i>=1;i--){
        vector<long long> next(dp.size()+(dp.size()-1)/i+1, 0);
        for(int j=0;j<dp.size();j++){
            for(int k=0;k<=K;k++){
                int x = k <= i ? j+(j+k)/i : j;
                next[x] = (next[x] + dp[j]) % MOD;
            }
        }
        dp = next;
    }
    long long res = K*(K+1)/2*N%MOD;
    for(int i=1;i<N;i++) res = (res * (K+1)) % MOD;
    for(int i=1;i<dp.size();i++){
        res = (res + MOD - (i*dp[i])%MOD) % MOD;
    }
    cout << res << endl;
}