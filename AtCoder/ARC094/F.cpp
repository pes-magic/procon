#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <queue>
#include <cstring>

using namespace std;

const int MOD = 998244353;

int solveSmall(const string& s){
    queue<string> qu; qu.push(s);
    set<string> S; S.insert(s);
    while(!qu.empty()){
        auto t = qu.front(); qu.pop();
        for(int i=0;i+1<t.size();i++){
            if(t[i] == t[i+1]) continue;
            for(int j=0;j<3;j++){
                if(t[i] == 'a'+j || t[i+1] == 'a'+j) continue;
                auto u = t;
                u[i] = u[i+1] = 'a' + j;
                if(!S.count(u)){
                    S.insert(u);
                    qu.push(u);
                }
            }
        }
    }
    return S.size();
}

int solve(const string& s){
    if(s.size() <= 3) return solveSmall(s);
    if(std::all_of(s.begin(), s.end(), [&](char c){ return c == s[0]; })) return 1;
    int dp[2][3][3][2];
    memset(dp, 0, sizeof(dp));
    for(int i=0;i<3;i++) dp[0][i][i][0] = 1;
    for(int i=1;i<s.size();i++){
        memset(dp[i%2], 0, sizeof(dp[0]));
        for(int prev=0;prev<3;prev++){
            for(int sum=0;sum<3;sum++){
                for(int adj=0;adj<2;adj++){
                    for(int next=0;next<3;next++){
                        dp[i%2][next][(sum+next)%3][adj || prev==next ? 1 : 0] += dp[1-i%2][prev][sum][adj];
                        dp[i%2][next][(sum+next)%3][adj || prev==next ? 1 : 0] %= MOD;
                    }
                }
            }
        }
    }
    int sum = 0;
    for(auto& c : s) sum = (sum + c - 'a') % 3;
    int res = 0;
    for(int i=0;i<3;i++) res = (res + dp[1-s.size()%2][i][sum][1]) % MOD;
    bool hasAdj = false;
    for(int i=0;i+1<s.size();i++) if(s[i] == s[i+1]) hasAdj = true;
    if(!hasAdj) res = (res+1)%MOD;
    return res;
}

int main(){
    string s; cin >> s;
    cout << solve(s) << endl;
}