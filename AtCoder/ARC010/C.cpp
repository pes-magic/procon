#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    int n, m, Y, Z;
    while(cin >> n >> m >> Y >> Z){
        vector<int> p(256, 0);
        vector<int> pos(256, -1);
        for(int i=0;i<m;i++){
            char c; int pt;
            cin >> c >> pt;
            p[c] = pt;
            pos[c] = i;
        }
        string b; cin >> b;
        vector<vector<long long>> dp(m+1, vector<long long>(1<<m, -(1LL << 60)));
        dp[m][0] = 0;
        for(auto& c : b){
            auto next = dp;
            int idx = pos[c];
            for(int prev=0;prev<=m;prev++){
                for(int s=0;s<(1<<m);s++){
                    next[idx][s|(1<<idx)] = max(next[idx][s|(1<<idx)], dp[prev][s] + p[c] + (prev == idx ? Y : 0));
                }
            }
            dp = next;
        }
        long long res = -(1LL << 60);
        for(int i=0;i<=m;i++){
            for(int j=0;j<(1<<m);j++){
                res = max(res, dp[i][j] + (j==(1<<m)-1 ? Z : 0));
            }
        }
        cout << res << endl;
    }
}