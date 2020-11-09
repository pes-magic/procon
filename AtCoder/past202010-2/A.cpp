#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<pair<int, int>> vp;
    for(int i=0;i<3;i++){
        int t; cin >> t;
        vp.emplace_back(t, i);
    }
    sort(vp.begin(), vp.end());
    cout << "ABC"[vp[1].second] << endl;
}