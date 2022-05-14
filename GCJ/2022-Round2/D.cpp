#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// only solves visible input
long long solve(const vector<int>& zero, const vector<int>& one, int C){
    vector<vector<long long>> dp(zero.size()+1, vector<long long>(one.size()+1, 1LL << 60));
    dp[zero.size()][one.size()] = 0;
    for(int i=zero.size();i>=0;i--){
        for(int j=one.size();j>=0;j--){
            if(i > 0) dp[i-1][j] = min(dp[i][j] + 2*zero[i-1], dp[i-1][j]);
            if(j > 0) dp[i][j-1] = min(dp[i][j] + 2*one[j-1], dp[i][j-1]);
            if(i > 1) dp[i-2][j] = min(dp[i][j] + C + 2*zero[i-1], dp[i-2][j]);
            if(j > 1) dp[i][j-2] = min(dp[i][j] + C + 2*one[j-1], dp[i][j-2]);
            if(i > 0 && j > 0) dp[i-1][j-1] = min(dp[i][j] + 2*max(zero[i-1], one[j-1]), dp[i-1][j-1]);
        }
    }
    return dp[0][0];
}

int main(){
    int T; cin >> T;
    for(int test=1;test<=T;test++){
        int N, C; cin >> N >> C;
        vector<int> zp, op, zm, om;
        for(int i=0;i<N;i++){
            int a, b; cin >> a >> b;
            if(a > 0){
                if(b == 0) zp.push_back(a);
                else op.push_back(a);
            } else {
                if(b == 0) zm.push_back(-a);
                else om.push_back(-a);
            }
        }
        sort(zp.begin(), zp.end());
        sort(op.begin(), op.end());
        sort(zm.begin(), zm.end());
        sort(om.begin(), om.end());
        cout << "Case #" << test << ": " << solve(zp, op, C) + solve(zm, om, C) << endl;;
    }
}