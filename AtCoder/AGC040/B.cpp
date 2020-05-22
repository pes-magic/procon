#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N; cin >> N;
    vector<int> L(N), R(N);
    for(int i=0;i<N;i++) cin >> L[i] >> R[i];
    int l = *max_element(L.begin(), L.end());
    int r = *min_element(R.begin(), R.end());
    int res = 0;
    for(int i=0;i<N;i++){
        if(L[i] != l || R[i] != r) res = max(res, max(r-l+1, 0) + R[i]-L[i]+1);
    }
    vector<pair<int, int>> vp;
    for(int i=0;i<N;i++){
        vp.emplace_back(max(0, R[i]-l+1), -max(0, r-L[i]+1));
    }
    sort(vp.rbegin(), vp.rend());
    vector<int> mr(N);
    mr[N-1] = -vp.back().second;
    for(int i=N-2;i>=0;i--) mr[i] = min(-vp[i].second, mr[i+1]);
    int ml = 1000000000;
    for(int i=0;i<N-1;i++){
        ml = min(ml, vp[i].first);
        res = max(res, ml+mr[i+1]);
    }
    cout << res << endl;
}