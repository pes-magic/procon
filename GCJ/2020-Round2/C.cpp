#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>

using namespace std;

int solve(const vector<pair<long long, long long>>& vp){
    const int N = vp.size();
    if(N==1) return 1;
    set<pair<long long, long long>> S;
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){
            auto dx = vp[j].first - vp[i].first;
            auto dy = vp[j].second - vp[i].second;
            if(dx < 0){
                dx = -dx;
                dy = -dy;
            } else if(dx == 0){
                dy = abs(dy);
            }
            S.emplace(dy, -dx);
        }
    }
    int res = 0;
    for(auto& dir : S){
        map<long long, int> mp;
        for(auto& p : vp){
            long long dt = p.first * dir.first + p.second * dir.second;
            if(!mp.count(dt)) mp[dt] = 0;
            ++mp[dt];
        }
        int cur = 0;
        int odd = 0;
        int odd3 = 0;
        for(auto it : mp){
            if(it.second%2 == 0) cur += it.second;
            else {
                if(it.second == 1){ ++odd; }
                else {
                    cur += it.second - 1;
                    ++odd3;
                }
            }
        }
        cur += odd3/2*2;
        odd3 %= 2;
        cur += min(odd+odd3, 2);
        res = max(res, cur);
    }
    return res;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N; cin >> N;
        vector<pair<long long, long long>> vp(N);
        for(auto& p : vp) cin >> p.first >> p.second;
        printf("Case #%d: %d\n", t, solve(vp));
    }
}