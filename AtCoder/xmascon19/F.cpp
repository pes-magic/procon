#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<vector<int>> convert(const vector<string>& S){
    vector<vector<int>> res(S.size());
    for(int i=0;i<S.size();i++){
        for(int j=0;j<S[i].size();j++){
            if(S[i][j] == '.') res[i].push_back(j);
        }
    }
    return res;
}

int search(const vector<vector<int>>& S, int W, vector<pair<int,int>>& stamp, int best){
    const int H = S.size();
    int minX = W, maxX = -1, minY = H, maxY = -1;
    auto range = [&](int i){
        int m = W, M = -1;
        for(auto& p : stamp){
            if(i < p.first || p.first+H/2 <= i) continue;
            m = min(m, p.second);
            M = max(M, p.second+W/2-1);
        }
        return make_pair(m, M);
    };
    for(int i=0;i<H;i++){
        if(S[i].empty()) continue;
        auto r = range(i);
        if(S[i][0] < r.first){ minX = min(minX, S[i][0]); maxX = max(maxX, S[i][0]); minY = min(minY, i); maxY = max(maxY, i); }
        if(S[i].back() > r.second){ minX = min(minX, S[i].back()); maxX = max(maxX, S[i].back()); minY = min(minY, i); maxY = max(maxY, i); } 
    }
    if(minX == W && maxX == -1) return stamp.size();
    if(maxX - minX <= W/2 - 1 && maxY - minY <= H/2 - 1) return stamp.size() + 1;
    if(stamp.size() + 2 >= best) return best;

    for(int i=0;i<H;i++){
        if(S[i].empty()) continue;
        bool ok = false;
        auto r = range(i);
        if(r.first <= S[i][0] && S[i].back() <= r.second) continue;
        int check = (S[i][0] < r.first ? S[i][0] : S[i].back());
        for(int j=max(0, check-(W/2-1));j<=check;j++){
            stamp.emplace_back(i, j);
            best = min(best, search(S, W, stamp, best));
            stamp.pop_back();
        }
        break;
    }
    return best;
}

int solve(const vector<vector<int>>& S, int W){
    vector<pair<int,int>> stamp;
    return search(S, W, stamp, 4);
}

int main(){
    int H, W;
    while(cin >> H >> W){
        vector<string> S(H);
        for(auto& s : S) cin >> s;
        cout << solve(convert(S), W) << endl;
    }
}