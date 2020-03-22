#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main(){
    int N, S;
    while(cin >> N >> S){
        vector<int> A(N);
        for(auto& t : A) cin >> t;
        vector<long long> dp(S, 0);
        long long res = 0;
        for(int i=0;i<N;i++){
            for(int j=S-1;j>0;j--){
                if(j+A[i] == S){
                    res += dp[j] * (N-i);
                    res %= MOD;
                } else if(j+A[i] < S){
                    dp[j+A[i]] += dp[j];
                    dp[j+A[i]] %= MOD;
                }
            }
            if(A[i] == S){
                res += (i+1) * (N-i);
                res %= MOD;
            } else if(A[i] < S){
                dp[A[i]] += (i+1);
                dp[A[i]] %= MOD;
            }
        }
        cout << res << endl;
    }
}