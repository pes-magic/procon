#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1000000007;

int main(){
    string S;
    while(cin >> S){
        vector<int> dp(13, 0);
        dp[0] = 1;
        int m = 1;
        for(int i=S.size()-1;i>=0;i--){
            vector<int> next(13, 0);
            for(int j=0;j<10;j++){
                if(S[i] == '?' || S[i]-'0' == j){
                    for(int k=0;k<13;k++){
                        int key = (m*j+k)%13;
                        next[key] = (next[key] + dp[k]) % MOD;
                    }
                }
            }
            dp = next;
            m = (10*m)%13;
        }
        cout << dp[5] << endl;
    }
}