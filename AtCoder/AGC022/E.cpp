#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

const int MOD = 1000000007;

long long solve(const string& S){
    vector<long long> dp(54, 0);
    dp[0] = 1;
    for(auto& c : S){
        vector<long long> next(54, 0);
        for(int has1=0;has1<2;has1++){
            for(int lead0=0;lead0<3;lead0++){
                for(int trail0=0;trail0<3;trail0++){
                    for(int sec1=0;sec1<3;sec1++){
                        int idx =  ((has1 * 3 + lead0) * 3 + trail0) * 3 + sec1;
                        if(c == '0' || c == '?'){
                            if(!has1){
                                int nlead0 = (lead0 == 2 ? 1 : lead0+1);
                                next[((has1 * 3 + nlead0) * 3 + trail0) * 3 + sec1] += dp[idx];
                            } else {
                                int ntrail0 = (trail0 == 2 ? 1 : trail0+1);
                                next[((has1 * 3 + lead0) * 3 + ntrail0) * 3 + sec1] += dp[idx];
                            }
                        }
                        if(c == '1' || c == '?'){
                            if(!has1){
                                next[((3 + lead0) * 3 + trail0) * 3 + sec1] += dp[idx];
                            } else {
                                if(lead0 == 0){
                                    if(trail0 == 0){
                                        next[((has1 * 3 + lead0) * 3 + trail0) * 3 + min(sec1+1, 2)] += dp[idx];
                                    } else {
                                        next[((has1 * 3 + lead0) * 3 + trail0 - 1) * 3 + sec1] += dp[idx];
                                    }
                                } else {
                                    if(trail0 == 0){
                                        next[((has1 * 3 + lead0 - 1) * 3 + trail0) * 3 + sec1] += dp[idx];
                                    } else if(trail0 == 1) {
                                        next[((has1 * 3 + lead0) * 3 + 0) * 3 + sec1] += dp[idx];
                                    } else {
                                        next[((has1 * 3 + 3 - lead0) * 3 + 0) * 3 + sec1] += dp[idx];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        for(auto& t : next) t %= MOD;
        dp = next;
    }
    long long res = 0;
    for(int trail0=0;trail0<3;trail0++){
        for(int sec1=trail0;sec1<3;sec1++){
            int idx =  27 + 3 * trail0 + sec1;
            res = (res + dp[idx]) % MOD;
        }
    }
    return res;
}

int main(){
    string S; cin >> S;
    cout << solve(S) << endl;
}