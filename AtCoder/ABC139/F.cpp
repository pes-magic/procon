#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

int main(){
    int N; cin >> N;
    vector<pair<long long, long long>> vp(N);
    for(auto& p : vp) cin >> p.first >> p.second;
    sort(vp.begin(), vp.end(), [](const pair<long long, long long>& p1, const pair<long long, long long>& p2){
        return atan2(p1.second, p1.first) < atan2(p2.second, p2.first);
    });
    double res = 0.0;
    for(int i=0;i<N;i++){
        long long x = 0, y = 0;
        for(int j=0;j<N;j++){
            x += vp[(i+j)%N].first;
            y += vp[(i+j)%N].second;
            res = max(res, hypot(x, y));
        }
    }
    printf("%.10lf\n", res);
}