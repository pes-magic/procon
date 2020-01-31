#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;
    while(cin >> n){
        vector<vector<int>> cnt(2, vector<int>(100001, 0));
        for(int i=0;i<n;i++){
            int v; cin >> v;
            cnt[i%2][v]++;
        }
        vector<vector<pair<int,int>>> vp(2, vector<pair<int,int>>(1, make_pair(n/2, 0)));
        for(int i=0;i<2;i++){
            for(int j=1;j<=100000;j++){
                if(cnt[i][j]) vp[i].emplace_back(n/2-cnt[i][j], j);
            }
        }
        for(auto& v : vp) sort(v.begin(), v.end());
        if(vp[0][0].second != vp[1][0].second){
            cout << vp[0][0].first + vp[1][0].first << endl;
        } else {
            cout << min(vp[0][0].first + vp[1][1].first, vp[0][1].first + vp[1][0].first) << endl;
        }
    }
}