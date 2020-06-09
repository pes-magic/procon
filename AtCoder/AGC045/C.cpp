#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    int N, A, B; cin >> N >> A >> B;
    if(A > B) swap(A, B);
    vector<long long> ones(B, 0);
    ones[1] = 1;
    for(int i=1;i<B;i++){
        if(i+1 < B) ones[i+1] = (ones[i+1] + ones[i]) % MOD;
        for(int j=i+A+1;j<B;j++) ones[j] = (ones[j] + ones[i]) % MOD;
    }
    vector dp(N+1, vector(2, 0LL));
    dp[0][0] = dp[0][1] = 1;
    long long res = 1;
    for(int i=0;i<N;i++) res = (2 * res) % MOD;
    for(int i=A;i<B;i++){
        for(int j=i+1;j<B;j++) dp[j][1] = (dp[j][1] + ones[j-i]) % MOD;
    }
    for(int i=0;i<N;i++){
        for(int j=i+1;j<min(i+A, N+1);j++){
            dp[j][0] = (dp[j][0] + dp[i][1]) % MOD;
        }
        for(int j=i+1;j<min(i+B, N+1);j++){
            auto add = dp[i][0] * ones[j-i] % MOD;
            if(N-i < B && N-j >= A) res = (res + MOD - add) % MOD;
            dp[j][1] = (dp[j][1] + add) % MOD;
        }
    }
    for(auto& t : dp.back()) res = (res + MOD - t) % MOD;
    cout << res << endl;
}