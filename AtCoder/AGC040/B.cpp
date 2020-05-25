#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N; cin >> N;
    vector<long long> L(N), R(N);
    for(int i=0;i<N;i++) cin >> L[i] >> R[i];
    auto maxL = *max_element(L.begin(), L.end());
    auto minR = *min_element(R.begin(), R.end());
    long long res = 0;
    for(int i=0;i<N;i++){
        res = max(res, max(0LL, minR-maxL+1) + R[i] - L[i] + 1);
    }
    vector<pair<long long, long long>> vp;
    for(int i=0;i<N;i++) vp.emplace_back(L[i], R[i]);
    sort(vp.begin(), vp.end(), [](auto& a, auto& b){ return a.second != b.second ? a.second > b.second : a.first > b.first; });
    vector<long long> tl(N), tr(N);
    tl.back() = vp.back().first;
    for(int i=N-2;i>=0;i--) tl[i] = max(tl[i+1], vp[i].first);
    tr[0] = vp[0].second;
    for(int i=1;i<N;i++) tr[i] = min(tr[i-1], vp[i].second);
    for(int i=1;i<N;i++){
        res = max(res, max(0LL, tr[i-1]-maxL+1) + max(0LL, minR-tl[i]+1));
    }
    cout << res << endl;
}