#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    int N, Q;
    while(cin >> N >> Q){
        vector<int> A(N);
        for(auto& t : A) cin >> t;
        vector<vector<long long>> dp(N, vector<long long>(N, 0));
        vector<vector<int>> time(N, vector<int>(N, 0));
        vector<long long> pow2(Q+1, 0);
        pow2[0] = 1;
        for(int i=1;i<=Q;i++) pow2[i] = (2*pow2[i-1])%MOD;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(A[i] > A[j]) ++dp[i][j];
            }
        }
        for(int i=0;i<Q;i++){
            auto getValue = [&](int x, int y){
                return (dp[x][y] * pow2[i - time[x][y]]) % MOD;
            };
            int X, Y; cin >> X >> Y;
            --X; --Y;
            for(int j=0;j<N;j++){
                if(j == X || j == Y) continue;
                auto next = (getValue(X, j) + getValue(Y, j)) % MOD;
                dp[X][j] = dp[Y][j] = next;
                time[X][j] = time[Y][j] = i+1;
                next = (getValue(j, X) + getValue(j, Y)) % MOD;
                dp[j][X] = dp[j][Y] = next;
                time[j][X] = time[j][Y] = i+1;
            }
            {
                auto next = (getValue(X, Y) + getValue(Y, X)) % MOD;
                dp[X][Y] = dp[Y][X] = next;
                time[X][Y] = time[Y][X] = i+1;
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                dp[i][j] = (dp[i][j] * pow2[Q-time[i][j]]) % MOD;
            }
        }
        long long res = 0;
        for(int i=0;i<N;i++){
            for(int j=i+1;j<N;j++) res = (res + dp[i][j]) % MOD;
        }
        cout << res << endl;
    }
}