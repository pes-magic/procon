#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    int N, M; cin >> N >> M;
    vector<long long> dp(M);
    dp[0] = 2;
    for(int i=1;i<M;i++) dp[i] = 2 * dp[i-1] % MOD;
    for(int i=1;i<N;i++){
        long long add = 0;
        for(int j=0;j<M;j++){
            long long cur = dp[j];
            dp[j] = (cur * (j+2) + add) % MOD;
            add = (2 * add + cur * (j+1)) % MOD;
        }
    }
    cout << dp.back() << endl;
}