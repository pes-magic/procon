#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int R, S; cin >> R >> S;
        vector<int> cnt(R, 1);
        int sum = R;
        vector<pair<int, int>> res;
        int idx = 0;
        for(int i=0;i<(R*(S-1))/2;i++){
            int s = cnt[idx] + cnt[(idx+1)%R];
            res.emplace_back(s, sum-s+1);
            ++cnt[idx];
            ++cnt[(idx+1)%R];
            sum += 2;
            idx = (idx+2)%R;
        }
        if((R*(S-1))%2) res.emplace_back(S-1, R*S-S+1);
        printf("Case #%d: %d\n", t, res.size());
        for(auto& p : res) cout << p.first << " " << p.second << endl;
    }
}