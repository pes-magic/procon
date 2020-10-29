#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int INF = 1000000007;

int main(){
    int N, M; cin >> N >> M;
    vector<int> w(N);
    for(auto& t : w) cin >> t;
    sort(w.begin(), w.end());
    vector<pair<int, int>> vp(M);
    for(auto& t : vp) cin >> t.second >> t.first;
    sort(vp.begin(), vp.end());
    if(vp[0].first < w[0]){
        cout << -1 << endl;
        return 0;
    }
    map<int, int> limit;
    limit[0] = 0;
    int longest = 0;
    for(auto& p : vp){
        if(p.second >= longest){
            limit[p.first] = p.second;
            longest = p.second;
        }
    }
    int res = INF;
    do {
        vector<int> dp(N, 0);
        dp[0] = 0;
        for(int i=0;i<N;i++){
            int sumW = w[i];
            for(int j=i+1;j<N;j++){
                sumW += w[j];
                auto it = limit.lower_bound(sumW);
                --it;
                dp[j] = max(dp[j], dp[i] + it->second);
            }
        }
        res = min(res, dp.back());
    } while(next_permutation(w.begin(), w.end()));
    cout << res << endl;
}
