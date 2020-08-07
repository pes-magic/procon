#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N; long long W;
    while(cin >> N >> W){
        vector<vector<long long>> v(2), w(2);
        for(int i=0;i<N;i++){
            long long a, b; cin >> a >> b;
            v[i%2].push_back(a);
            w[i%2].push_back(b);
        }
        vector<vector<pair<long long, long long>>> vp(2);
        for(int i=0;i<2;i++){
            for(int j=0;j<(1<<v[i].size());j++){
                long long sumV = 0, sumW = 0;
                for(int k=0;k<v[i].size();k++){
                    if(j&(1<<k)){
                        sumV += v[i][k];
                        sumW += w[i][k];
                    }
                }
                if(sumW > W) continue;
                vp[i].emplace_back(sumW, sumV);
            }
            sort(vp[i].begin(), vp[i].end());
            long long m = 0;
            for(auto& p : vp[i]){
                m = max(m, p.second);
                p.second = m;
            }
        }
        int idx = vp[1].size() - 1;
        long long res = 0;
        for(auto& p : vp[0]){
            while(p.first + vp[1][idx].first > W) --idx;
            res = max(res, p.second + vp[1][idx].second);
        }
        cout << res << endl;
    }
}