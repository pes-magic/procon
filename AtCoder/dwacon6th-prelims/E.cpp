#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

int main(){
    int N, X;
    while(cin >> N >> X){
        vector<int> L(N);
        for(auto& t : L) cin >> t;
        sort(L.rbegin(), L.rend());
        vector<vector<long long>> dp(1, vector<long long>(X+1, 0));
        dp[0][0] = 1;
        for(auto& l : L){
            vector<vector<long long>> next(X/l+1, vector<long long>(X+1, 0));
            for(int i=0;i<dp.size();i++){
                for(int j=0;j<dp[i].size();j++){
                    if(!dp[i][j]) continue;
                    if(j+l <= X){
                        next[i+1][j+l] += dp[i][j];
                        next[i+1][j+l] %= MOD;
                    }
                    next[i][j] += dp[i][j] * (j - i*(l-1) + MOD);
                    next[i][j] %= MOD;
                    for(int d=1;d<=l-1;d++){
                        if(j+d > X) break;
                        next[i][j+d] += 2 * i * dp[i][j];
                        next[i][j+d] %= MOD;
                    }
                    if(i >= 2){
                        for(int d=0;d<=l-2;d++){
                            if(j+d > X) break;
                            next[i-1][j+d] += i * (i-1) * (l-d-1) * dp[i][j];
                            next[i-1][j+d] %= MOD;
                        }
                    }
                }
            }
            dp = next;
        }
        long long res = 0;
        long long f = 1;
        for(int i=1;i<dp.size();i++){
            f = (f*i)%MOD;
            res += f * dp[i][X];
            res %= MOD;
        }
        cout << res << endl;
    }
}