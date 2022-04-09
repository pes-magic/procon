#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve(){
    int E, W; cin >> E >> W;
    vector<vector<int>> X(E, vector<int>(W, 0));
    vector<int> sum(E, 0);
    for(auto& v : X){
        for(auto& t : v) cin >> t;
    }
    for(int i=0;i<E;i++){
        for(int j=0;j<W;j++) sum[i] += X[i][j];
    }
    vector<vector<int>> common(E+1, vector<int>(E+1, 0));
    vector<vector<int>> dp(E+1, vector<int>(E+1, 0));
    for(int dif=1;dif<=E;dif++){
        for(int i=0;i+dif<=E;i++){
            vector<int> cm(W, 10000);
            for(int j=i;j<i+dif;j++){
                for(int k=0;k<W;k++) cm[k] = min(cm[k], X[j][k]);
            }
            for(int k=0;k<W;k++){
                common[i][i+dif] += cm[k];
            }
            for(int j=i;j<i+dif;j++){
                dp[i][i+dif] += 2 * (sum[j] - common[i][i+dif]);
            }
            for(int sep=i+1;sep<i+dif;sep++){
                int score = 2 * (common[i][sep] - common[i][i+dif]) + dp[i][sep] + 2 * (common[sep][i+dif] - common[i][i+dif]) + dp[sep][i+dif];
                dp[i][i+dif] = min(dp[i][i+dif], score);
            }
        }
    }
    return 2 * common[0][E] + dp[0][E];
}

int main(){
    int T; cin >> T;
    for(int test=1;test<=T;test++){
        cout << "Case #" << test << ": " << solve() << endl;;
    }
}