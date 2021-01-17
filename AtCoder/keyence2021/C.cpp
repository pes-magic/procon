#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 998244353;

int main(){
    int H, W, K; cin >> H >> W >> K;
    vector<long long> pow3(5001, 1);
    for(int i=1;i<=5000;i++) pow3[i] = 3*pow3[i-1]%MOD;
    vector<string> vs(H, string(W, '?'));
    for(int _=0;_<K;_++){
        int h, w; char c; cin >> h >> w >> c;
        vs[h-1][w-1] = c;
    }
    vector<vector<long long>> dp(H, vector<long long>(W, 0));
    vector<int> sum(W, 0);
    dp[H-1][W-1] = (vs[H-1][W-1] == '?' ? 3 : 1);
    for(int i=W-2;i>=0;i--){
        if(vs[H-1][i] == '?'){
            dp[H-1][i] = (2 * dp[H-1][i+1]) % MOD;
            sum[i] = 1;
        } else if(vs[H-1][i] != 'D'){
            dp[H-1][i] = dp[H-1][i+1];
        }
    }
    for(int j=H-2;j>=0;j--){
        int sel = 0;
        if(vs[j][W-1] == '?'){
            dp[j][W-1] = (2 * dp[j+1][W-1]) % MOD;
            ++sel;
        } else if(vs[j][W-1] != 'R') {
            dp[j][W-1] = dp[j+1][W-1];
        }
        for(int i=W-2;i>=0;i--){
            if(vs[j][i] == '?'){
                dp[j][i] = (dp[j][i] + 2 * dp[j][i+1] * pow3[sum[i]]) % MOD;
            } else if(vs[j][i] != 'D'){
                dp[j][i] = (dp[j][i] + dp[j][i+1] * pow3[sum[i]]) % MOD;
            }
            if(vs[j][i] == '?'){
                dp[j][i] = (dp[j][i] + 2 * dp[j+1][i] * pow3[sel]) % MOD;
            } else if(vs[j][i] != 'R'){
                dp[j][i] = (dp[j][i] + dp[j+1][i] * pow3[sel]) % MOD;
            }
            if(vs[j][i] == '?'){
                ++sum[i];
                ++sel;
            }
        }
    }
    cout << dp[0][0] << endl;
}