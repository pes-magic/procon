#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000000007;

int solve(const vector<pair<int,int>>& v, int W){
    vector<int> step(W+2, 0);
    for(int i=0;i<v.size(); ){
        int end = i;
        while(end < v.size() && v[i].first == v[end].first && v[i].second + end - i == v[end].second) ++end;
        int s = v[i].second - 1;
        int e = v[end-1].second + 1; 
        for(int j=s+1;j<=e-1;j++){
            step[s] = min(step[s], step[j]+j-s);
            step[e] = min(step[e], step[j]+e-j);
            step[j] = INF;
        }
        i = end;
    }
    int res = INF;
    for(int i=1;i<=W;i++) res = min(res, step[i]);
    return res;
}

int main(){
    int W, H, Q;
    while(cin >> W >> H >> Q){
        vector<vector<pair<int, int>>> vp(2);
        for(int i=0;i<Q;i++){
            int t, d, x; cin >> t >> d >> x;
            vp[d].emplace_back(t, x);
        }
        for(auto& v : vp) sort(v.begin(), v.end());
        int res = solve(vp[0], W) + solve(vp[1], H);
        cout << (res < INF ? res : -1) << endl;
    }
}
