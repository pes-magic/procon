#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

const int MOD = 1000000007;

int main(){
    int N, K;
    while(cin >> N >> K){
        string S; cin >> S;
        vector<vector<int>> dp(K+1, vector<int>(K+1, 0));
        dp[0][0] = 1;
        for(auto& c : S){
            vector<vector<int>> next(K+1, vector<int>(K+1, 0));
            for(int i0=0;i0<=K;i0++){
                for(int i1=0;i1<=K;i1++){
                    if((c == '0' || c == '?') && i0 < K){
                        next[i0+1][max(0, i1-1)] += dp[i0][i1];
                        next[i0+1][max(0, i1-1)] %= MOD;
                    }
                    if((c == '1' || c == '?') && i1 < K){
                        next[max(0, i0-1)][i1+1] += dp[i0][i1];
                        next[max(0, i0-1)][i1+1] %= MOD;
                    }
                }
            }
            dp = next;
        }
        int res = 0;
        for(auto& v : dp){
            res += accumulate(v.begin(), v.end(), 0LL) % MOD;
            res %= MOD;
        }
        cout << res << endl;
    }
}