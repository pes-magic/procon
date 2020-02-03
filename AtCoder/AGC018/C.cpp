#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<long long> solve(const vector<pair<long long, long long>>& vp, long long X, long long Z){
    priority_queue<long long> qu;
    long long cur = 0;
    for(int i=0;i<X;i++){
        cur += vp[i].first;
        qu.emplace(vp[i].second - vp[i].first);
    }
    vector<long long> res;
    res.push_back(cur);
    for(int i=X;i<X+Z;i++){
        cur += vp[i].first;
        qu.emplace(vp[i].second - vp[i].first);
        cur += qu.top(); qu.pop();
        res.push_back(cur);
    }
    return res;
}

int main(){
    int X, Y, Z;
    while(cin >> X >> Y >> Z){
        vector<vector<long long>> C(X+Y+Z, vector<long long>(3));
        for(auto& v : C){
            for(auto& t : v) cin >> t;
        }
        sort(C.begin(), C.end(), [](const vector<long long>& a, const vector<long long>& b){ return a[0]-a[1] > b[0]-b[1]; });
        vector<vector<long long>> res;
        for(int i=0;i<2;i++){
            vector<pair<long long, long long>> vp;
            for(auto& c : C) vp.emplace_back(c[i], c[2]);
            res.emplace_back(solve(vp, i==0?X:Y, Z));
            reverse(C.begin(), C.end());
        }
        long long best = 0;
        for(int i=0;i<=Z;i++) best = max(best, res[0][i] + res[1][Z-i]);
        cout << best << endl;
    }
}