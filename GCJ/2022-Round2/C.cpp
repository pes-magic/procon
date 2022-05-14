#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long dist(const pair<int, int>& a, const pair<int, int>& b){
    long long dx = a.first - b.first;
    long long dy = a.second - b.second;
    return dx*dx + dy*dy;
}

// only solves visible input
vector<pair<int,int>> solve(const vector<pair<int,int>>& child, const vector<pair<int,int>>& sweet){
    int N = child.size();
    vector<pair<int,int>> res;
    if(N > 10) return res;
    vector<int> dp(1<<(2*N), -1);
    dp[0] = -2;
    for(int i=0;i<(1<<(2*N));i++){
        if(dp[i] == -1) continue;
        for(int j=0;j<N;j++){
            if(i&(1<<j)) continue;
            long long nearest = dist(child[j], sweet[0]);
            vector<int> nearestSweets; nearestSweets.push_back(0);
            for(int k=0;k<N;k++){
                if(i&(1<<(N+k))) continue;
                long long cur = dist(child[j], sweet[k+1]);
                if(cur < nearest){
                    nearestSweets.clear();
                    nearest = cur;
                }
                if(cur == nearest){
                    nearestSweets.push_back(k+1);
                }
            }
            for(auto& k : nearestSweets){
                if(k == 0) continue;
                dp[i|(1<<j)|(1<<(N+k-1))] = 256*j + k - 1;
            }
        }
    }
    int b = (1<<(2*N))-1;
    if(dp[b] == -1) return res;
    while(b){
        int j = dp[b]/256;
        int k = dp[b]%256;
        res.emplace_back(j+1, k+2);
        b ^= 1<<j;
        b ^= 1<<(N+k);
    }
    reverse(res.begin(), res.end());
    return res;
}

int main(){
    int T; cin >> T;
    for(int test=1;test<=T;test++){
        int N; cin >> N;
        vector<pair<int,int>> child(N);
        vector<pair<int,int>> sweets(N+1);
        for(auto& p : child) cin >> p.first >> p.second;
        for(auto& p : sweets) cin >> p.first >> p.second;
        cout << "Case #" << test << ": ";
        auto res = solve(child, sweets);
        if(res.empty()){
            cout << "IMPOSSIBLE" << endl;
        } else {
            cout << "POSSIBLE" << endl;
            for(auto& p : res) cout << p.first << " " << p.second << endl;
        }
    }
}