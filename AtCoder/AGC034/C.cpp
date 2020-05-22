#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    long long N, X; cin >> N >> X;
    vector<long long> b(N), l(N), u(N);
    for(int i=0;i<N;i++) cin >> b[i] >> l[i] >> u[i];
    vector<pair<long long, int>> vp;
    for(int i=0;i<N;i++) vp.emplace_back((X-b[i])*u[i] + b[i]*l[i], i);
    sort(vp.rbegin(), vp.rend());
    long long thr = 0;
    for(int i=0;i<N;i++) thr += b[i] * l[i];
    long long L = -1, R = N*X;
    while(R-L > 1){
        long long mid = (L+R)/2;
        long long sum = 0;
        int div = mid/X;
        for(int i=0;i<div;i++) sum += vp[i].first;
        long long cur = 0;
        long long m = mid%X;
        for(int i=0;i<N;i++){
            int idx = vp[i].second;
            long long add = min(m, b[idx]) * l[idx] + max(0LL, m-b[idx]) * u[idx];
            if(i < div) cur = max(cur, sum - vp[i].first + vp[div].first + add);
            else cur = max(cur, sum + add);
        }
        if(cur >= thr) R = mid;
        else L = mid;
    }
    cout << R << endl;
}