#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N; cin >> N;
    vector<int> A(1<<N);
    for(auto& t : A) cin >> t;
    vector dp(1<<N, vector(2, 0));
    for(int i=0;i<(1<<N);i++){
        if(A[0] > A[i]) dp[i][1] = i;
        else dp[i][0] = i;
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<(1<<N);j++){
            if(!(j&(1<<i))) continue;
            int src = j^(1<<i);
            for(auto& t : dp[src]){
                if(dp[j][0] != t && dp[j][1] != t){
                    if(A[t] > A[dp[j][0]]){
                        dp[j][1] = dp[j][0];
                        dp[j][0] = t;
                    } else if(A[t] > A[dp[j][1]]){
                        dp[j][1] = t;
                    }
                }
            }
        }
    }
    int res = 0;
    for(int i=1;i<(1<<N);i++){
        res = max(res, A[dp[i][0]] + A[dp[i][1]]);
        cout << res << endl;
    }
}