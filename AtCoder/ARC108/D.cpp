#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    int N; cin >> N;
    char aa, ab, ba, bb; cin >> aa >> ab >> ba >> bb;
    if(ab == 'A' ? aa == 'A' : bb == 'B'){
        cout << 1 << endl;
        return 0;
    }
    if((ab == 'B' && bb == 'A' && ba == 'A') || (ab == 'A' && aa == 'B' && ba == 'B')){
        long long res = 1;
        for(int i=3;i<N;i++) res = 2*res % MOD;
        cout << res << endl;
        return 0;
    }
    vector<int> dp(2, 0);
    dp[0] = 1;
    for(int i=3;i<N;i++){
        vector<int> next(2, 0);
        next[0] = (dp[0] + dp[1]) % MOD;
        next[1] = dp[0];
        dp = next;
    }
    cout << (dp[0] + dp[1]) % MOD << endl;
}