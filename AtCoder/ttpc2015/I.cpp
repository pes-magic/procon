#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <cstdio>

using namespace std;

vector<pair<int, int>> solve(const vector<int>& _P){
    auto P = _P;
    const int N = P.size();
    vector<pair<int, int>> res;
    while(res.size() <= 100000){
        int one = 0;
        for(int i=0;i<N;i++) if(P[i] == 1) one = i;
        int len = 1;
        while(one+len < N && P[one+len] == len+1) ++len;
        if(len == N) break;
        int target = 0;
        for(int i=0;i<N;i++) if(P[i] == len+1) target = i;
        if(one < target){
            for(int i=1;i<=len;i++){
                res.emplace_back(one+1, one+i+1);
                swap(P[one], P[one+i]);
            }
        } else {
            for(int i=len;i>=1;i--){
                res.emplace_back(one, one+i);
                swap(P[one-1], P[one-1+i]);
            }
        }
    }
    return res;
}

int main(){
    int N; cin >> N;
    vector<int> P(N);
    for(auto& t : P) cin >> t;
    auto res = solve(P);
    if(res.size() > 100000){
        cout << "MuriyarokonnNaN " << endl;
    } else {
        cout << res.size() << endl;
        for(auto& p : res) cout << p.first << " " << p.second << endl;
    }
}