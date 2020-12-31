#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1000000007;

int main(){
    int N; cin >> N;
    string S; cin >> S;
    vector<int> all(N+1, 0);
    all.back() = 7;
    vector<int> dp(N, 0);
    vector<int> next(4, N+1);
    int sum = 0;
    for(int i=N-1;i>=0;i--){
        int v = S[i]-'A'+1;
        sum ^= v;
        all[i] = all[i+1]&(1<<(v-1));
        {
            vector<int> nn(4, N+1);
            for(int j=0;j<4;j++) nn[j^v] = next[j];
            nn[v] = i+1;
            next = nn;
        }
        bool toOne = (sum && !all[i]);
        for(int j=1;j<=3;j++){
            int x = next[j];
            if(x > N) continue;
            if(all[x]){
                if((all[x]&(1<<(j-1))) && x == i+1){
                    dp[i] = (dp[i] + 1) % MOD;
                } else {
                    int seq = (N-x);
                    dp[i] = (dp[i] + 1 + seq/2) % MOD;
                    if(seq%2 == 0) toOne = false;
                }
            } else {
                dp[i] = (dp[i] + dp[x]) % MOD;
            }
        }
        if(toOne) dp[i] = (dp[i]+1) % MOD;
    }
    cout << dp.front() << endl;
}