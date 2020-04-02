#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

bool reachable(const vector<vector<int>>& g, const vector<int>& D, int H){
    const int N = g.size();
    vector<vector<int>> dp(N, vector<int>(H+1, 0));
    for(int i=1;i<=H;i++) dp.back()[i] = 1;
    for(int i=N-2;i>=0;i--){
        for(int j=0;j<=H;j++){
            bool valid = !g[i].empty();
            for(auto& t : g[i]) if(j <= D[t]) valid = false;
            if(!valid) continue;
            for(auto& t : g[i]){
                if(dp[t][j-D[t]]) dp[i][j] = 1;
            }
        }
    }
    return dp[0][H] == 1;
}

int main(){
    int N, M, H;
    while(cin >> N >> M >> H){
        vector<vector<int>> g(N);
        for(int i=0;i<M;i++){
            int f, t; cin >> f >> t;
            g[f-1].push_back(t-1);
        }
        vector<int> D(N);
        for(auto& t : D) cin >> t;
        if(!reachable(g, D, H)){
            cout << -1 << endl;
            continue;
        }
        double L = 0, R = 1e12;
        double test[] = {1, 2, 3, 4, 5, 6, 7};
       for(int _=0;_<1000;_++){
            double mid = 0.5*(L+R);
            vector<vector<double>> dp(N, vector<double>(H+1, 1e12));
            for(int i=1;i<=H;i++) dp.back()[i] = 0;
            for(int i=N-2;i>=0;i--){
                for(int j=0;j<=H;j++){
                    dp[i][j] = (H-j) + mid;
                    bool valid = !g[i].empty();
                    for(auto& t : g[i]) if(j <= D[t]) valid = false;
                    if(!valid) continue;
                    double prog = 0.0;
                    for(auto& t : g[i]) prog += dp[t][j-D[t]];
                    prog /= g[i].size();
                    dp[i][j] = min(dp[i][j], 1.0 + prog);
                }
            }
            if(dp[0][H] < mid) R = mid;
            else L = mid;
        }
        printf("%.12lf\n", 0.5*(L+R));
    }
}