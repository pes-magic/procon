#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

const int MOD = 998244353;

int main(){
    string S; cin >> S;
    int K; cin >> K;
    vector<int> seg;
    int cnt = 0;
    for(int i=S.size()-1;i>=0;i--){
        if(S[i] == '0'){
            seg.push_back(cnt);
            cnt = 0;
        } else {
            cnt++;
        }
    }
    K = min(K, accumulate(seg.begin(), seg.end(), 0));
    vector dp = vector(seg.size()+1, vector(K+1, vector(K+1, 0LL)));
    dp[0][0][0] = 1;
    int upper = 0;
    for(int i=0;i<seg.size();i++){
        for(int hold=0;hold<=upper;hold++){
            for(int op=0;op<=upper;op++){
                for(int j=0;j<=hold;j++){
                    dp[i+1][hold-j][op] = (dp[i+1][hold-j][op] + dp[i][hold][op]) % MOD;
                }
                for(int j=1;j<=min(seg[i], K-max(hold,op));j++){
                    dp[i+1][hold+j][op+j] = (dp[i+1][hold+j][op+j] + dp[i][hold][op]) % MOD;
                }
            }
        }
        upper = min(upper + seg[i], K);
    }
    long long res = 0;
    for(int i=0;i<=K;i++){
        for(int j=0;j<=K;j++){
            res = (res + dp.back()[i][j]) % MOD;
        }
    }
    cout << res << endl;
}