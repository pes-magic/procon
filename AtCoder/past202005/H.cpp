#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, L; cin >> N >> L;
    vector<long long> dp(L+10, 1LL << 60);
    vector<int> h(L+10, 0);
    for(int i=0;i<N;i++){
        int x; cin >> x;
        h[x] = 1;
    }
    long long T1, T2, T3; cin >> T1 >> T2 >> T3;
    dp[0] = 0;
    for(int i=0;i<L;i++){
        dp[i+1] = min(dp[i+1], dp[i] + T1 + h[i+1] * T3);
        dp[i+2] = min(dp[i+2], dp[i] + T1 + T2 + h[i+2] * T3);
        dp[i+4] = min(dp[i+4], dp[i] + T1 + 3*T2 + h[i+4]*T3);
    }
    long long res = dp[L];
    for(int i=1;i<=3;i++){
        if(L-i < 0) continue;
        res = min(res, dp[L-i] + T1/2 + T2/2 + T2*(i-1));
    }
    cout << res << endl;
 }