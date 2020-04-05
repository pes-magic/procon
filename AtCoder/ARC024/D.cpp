#include <iostream>
#include <vector>
#include <set>

using namespace std;

void solve(vector<pair<int, int>>& res, const vector<vector<int>>& pt, int begin, int end, int M){
    if(M <= 1) return;
    int mid = -1;
    int sum = 0, sizeL = 0, sizeR = 0;
    for(int i=begin;i<end;i++){
        sum += pt[i].size();
        if(sum >= M/2){
            mid = i;
            sizeR = M - sum;
            sizeL = sum - pt[i].size();
            break;
        }
    }
    set<int> y;
    set<int> ex;
    for(int i=begin;i<end;i++){
        for(auto& t : pt[i]){
            if(i==mid) ex.insert(t);
            else y.insert(t);
        }
    }
    for(auto& t : y){
        if(ex.count(t)) continue;
        res.push_back(make_pair(mid, t));
    }
    solve(res, pt, begin, mid, sizeL);
    solve(res, pt, mid+1, end, sizeR);
}

int main(){
    int M;
    while(cin >> M){
        vector<vector<int>> pt(1001);
        for(int i=0;i<M;i++){
            int x, y; cin >> x >> y;
            pt[x].push_back(y);
        }
        vector<pair<int, int>> res;
        solve(res, pt, 1, 1001, M);
        cout << res.size() << endl;
        for(auto& p : res) cout << p.first << " " << p.second << endl;
    }
}