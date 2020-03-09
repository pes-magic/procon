#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    long long L, R;
    while(cin >> L >> R){
        vector<vector<long long>> dp(2, vector<long long>(2, 0LL));
        for(int i=60;i>=0;i--){
            vector<vector<long long>> next(2, vector<long long>(2, 0LL));
            for(int l=0;l<=1;l++){
                for(int r=0;r<=1;r++){
                    if(!dp[l][r]) continue;
                    int low = (L>>i)%2;
                    int high = (R>>i)%2;
                    for(int d0=0;d0<=1;d0++){
                        for(int d1=d0;d1<=1;d1++){
                            if(l == 1 && d0 < low) continue;
                            if(r == 1 && d1 > high) continue;
                            int nl = (l && d0 == low ? 1 : 0);
                            int nr = (r && d1 == high ? 1 : 0);
                            next[nl][nr] = (next[nl][nr] + dp[l][r]) % MOD;
                        }
                    }
                }
            }
            if((L>>i) <= 1 && 1 <= (R>>i)){
                ++next[(L>>i) == 1 ? 1 : 0][(R>>i) == 1 ? 1 : 0];
            }
            dp = next;
        }
        long long res = 0;
        for(auto& v : dp){
            for(auto& t : v) res = (res + t) % MOD;
        }
        cout << res << endl;
    }
}