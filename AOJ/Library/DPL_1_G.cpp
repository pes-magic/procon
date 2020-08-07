#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int main(){
    int N, W;
    while(cin >> N >> W){
        vector<int> dp(W+1, 0);
        for(int i=0;i<N;i++){
            int v, w, m; cin >> v >> w >> m;
            for(int j=0;j<w;j++){
                if(j > W) break;
                deque<pair<int, int>> qu; qu.emplace_back(dp[j], 0);
                for(int k=1;j+k*w<=W;k++){
                    auto cur = dp[j+k*w] - k*v;
                    dp[j+k*w] = max(dp[j+k*w], qu.front().first + k * v);
                    while(!qu.empty() && k - qu.front().second >= m) qu.pop_front();
                    while(!qu.empty() && qu.back().first <= cur) qu.pop_back();
                    qu.emplace_back(cur, k);
                }
            }
        }
        cout << dp.back() << endl;
    }
}