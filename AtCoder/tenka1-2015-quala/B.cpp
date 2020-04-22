#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <cstdio>

using namespace std;

int getTime(const string& stamp){
    int h, m, s, s2;
    sscanf(stamp.c_str(), "%d:%d:%d.%d", &h, &m, &s, &s2);
    return  ((60 * (h-21) + m ) * 60 + s) * 1000 + s2;
}

vector<int> solve(const vector<pair<int, int>>& vp){
    const int N = vp.size();
    int left = -1000000000, right = 1000000000;
    for(auto& p : vp){
        if(p.first < p.second) continue;
        left = max(left, p.first-999);
        right = min(right, p.second);
    }
    if(right - left > 100000) return vector<int>(N, -1);
    vector<set<int>> s(N);
    for(int i=left;i<=right;i++){
        for(int j=0;j<N;j++){
            int d = vp[j].second - vp[j].first;
            if(vp[j].first < i && i+999 < vp[j].second) s[j].insert(d + 1000);
            else if(vp[j].second < i || i+999 < vp[j].first) s[j].insert(d);
            else {
                if(d > 0) s[j].insert(d);
                s[j].insert(d+1000);
            }
        }
    }
    vector<int> res(N);
    for(int i=0;i<N;i++) res[i] = s[i].size() == 1 ? *s[i].begin() : -1;
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<pair<int,int>> vp;
        for(int i=0;i<N;i++){
            string S, E; cin >> S >> E;
            vp.emplace_back(getTime(S), getTime(E));
        }
        auto res = solve(vp);
        for(auto& t : res) cout << t << endl;
    }
}
