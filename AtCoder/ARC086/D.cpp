#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<int> a(N);
        for(auto& t : a) cin >> t;
        int mIdx = distance(a.begin(), min_element(a.begin(), a.end()));
        int MIdx = distance(a.begin(), max_element(a.begin(), a.end()));
        vector<pair<int,int>> res;
        if(-a[mIdx] < a[MIdx]){
            res.emplace_back(MIdx+1, 1);
            for(int i=1;i+1<=N;i++) res.emplace_back(i, i+1);
        } else {
            res.emplace_back(mIdx+1, N);
            for(int i=N;i-1>=1;i--) res.emplace_back(i, i-1);
        }
        cout << 2*res.size() << endl;
        for(auto& p : res){
            for(int i=0;i<2;i++) cout << p.first << " " << p.second << endl;
        }
    }
}