#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    int N; cin >> N;
    vector<int> last(200001, -1);
    vector<int> next(N, -1);
    for(int i=0;i<N;i++){
        int c; cin >> c;
        if(last[c] != -1) next[last[c]] = i;
        last[c] = i;
    }
    vector<long long> dp(N, 0);
    dp[0] = 1;
    for(int i=0;i<N;i++){
        dp[i+1] = (dp[i+1] + dp[i]) % MOD;
        if(next[i] != -1 && next[i] != i+1){
            dp[next[i]] = (dp[next[i]] + dp[i]) % MOD;
        }
    }
    cout << dp.back() << endl;
}