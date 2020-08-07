#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

class Item {
public:
    long long v, w, m;
    explicit Item(long long v, long long w, long long m) : v(v), w(w), m(m) {}
    bool operator < (const Item& it) const { return v * it.w < it.v * w; }
};

int main(){
    int N, W;
    while(cin >> N >> W){
        vector<long long> dp(50*50*N+1, W+1);
        dp[0] = 0;
        vector<Item> vi;
        for(int i=0;i<N;i++){
            long long v, w, m; cin >> v >> w >> m;
            if(m > 50) vi.emplace_back(v, w, m-50);
            m = min(50LL, m);
            for(int j=0;j<v;j++){
                deque<pair<long long, long long>> qu; qu.emplace_back(dp[j], 0);
                for(int k=1;j+k*v<dp.size();k++){
                    auto cur = dp[j+k*v] - k*w;
                    dp[j+k*v] = min(dp[j+k*v], qu.front().first + k * w);
                    while(!qu.empty() && k - qu.front().second >= m) qu.pop_front();
                    while(!qu.empty() && qu.back().first >= cur) qu.pop_back();
                    qu.emplace_back(cur, k);
                }
            }
        }
        sort(vi.rbegin(), vi.rend());
        long long res = 0;
        for(int i=0;i<dp.size();i++){
            if(dp[i] > W) continue;
            long long curV = i;
            long long curW = dp[i];
            for(auto& it : vi){
                auto r = min(it.m, (W-curW)/it.w);
                curV += r * it.v;
                curW += r * it.w;
            }
            res = max(res, curV);
        }
        cout << res << endl;
    }
}