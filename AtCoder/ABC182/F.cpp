#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N; cin >> N;
    long long X; cin >> X;
    vector<long long> A(N);
    for(auto& t : A) cin >> t;
    vector<long long> cnt(N, 0);
    long long rest = X;
    for(int i=N-1;i>=0;i--){
        cnt[i] = rest/A[i];
        rest %= A[i];
    }
    vector dp(N, vector(2, 0LL));
    dp[0][0] = 1;
    for(int i=0;i<N-1;i++){
        dp[i+1][0] += dp[i][0];
        if(cnt[i] != 0) dp[i+1][1] += dp[i][0];
        if(i+1 < N){
            if((cnt[i]+1)*A[i] == A[i+1]) dp[i+1][1] += dp[i][1];
            else {
                dp[i+1][0] += dp[i][1];
                dp[i+1][1] += dp[i][1];
            }
        }
    }
    cout << dp.back()[0] + dp.back()[1] << endl;
}