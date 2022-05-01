#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int T; cin >> T;
    for(int test=1;test<=T;test++){
        int N, P; cin >> N >> P;
        vector<vector<int>> X(N+1, vector<int>(P));
        for(int i=0;i<P;i++) X[0][i] = 0;
        for(int i=1;i<=N;i++){
            for(int j=0;j<P;j++) cin >> X[i][j];
        }
        vector<long long> dp(P, 0LL);
        for(int i=1;i<=N;i++){
            vector<long long> next(P, 1LL << 50);
            long long m = *min_element(X[i].begin(), X[i].end());
            long long M = *max_element(X[i].begin(), X[i].end());
            for(int j=0;j<P;j++){
                for(int k=0;k<P;k++){
                    next[k] = min(next[k], dp[j] + abs(X[i-1][j]-m) + (M-m) + abs(X[i][k]-M));
                    next[k] = min(next[k], dp[j] + abs(X[i-1][j]-M) + (M-m) + abs(X[i][k]-m));
                }
            }
            dp = next;
        }
        cout << "Case #" << test << ": " << *min_element(dp.begin(), dp.end()) << endl;
    }
}