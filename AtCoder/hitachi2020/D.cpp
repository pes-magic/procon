#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N, T;
    while(cin >> N >> T){
        vector<pair<long long, long long>> vp;
        vector<int> z;
        for(int i=0;i<N;i++){
            int a, b; cin >> a >> b;
            if(a == 0){
                z.push_back(b);
            } else {
                vp.emplace_back(a, b);
            }
        }
        sort(vp.begin(), vp.end(), [](auto a, auto b){ return b.first*(a.second+1) < a.first*(b.second+1); });
        sort(z.begin(), z.end());
        vector<long long> dp(50, T+1);
        dp[0] = 0;
        for(auto& p : vp){
            for(int i=dp.size()-2;i>=0;i--){
                if(dp[i] > T) continue;
                dp[i+1] = min(dp[i+1], (p.first+1) * (dp[i]+1) + p.second);
            }
        }
        int res = 0;
        for(int i=0;i<dp.size();i++){
            if(dp[i] > T) continue;
            long long t = dp[i];
            int cur = i;
            for(auto& v : z){
                if(t + v + 1 > T) break;
                t += v + 1;
                ++cur;
            }
            res = max(res, cur);
        }
        cout << res << endl;
    }
}