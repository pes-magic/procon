#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

template<typename T>
int LIS(const vector<T>& v){
    if(v.empty()) return 0;
    vector<T> a(v.size(), v[0]);
    auto end = a.begin();
    ++end;
    for(int i=1;i<v.size();i++){
        auto l = lower_bound(a.begin(), end, v[i]);
        if(l == end) ++end;
        *l = v[i];
    }
    return distance(a.begin(), end);
}

int main(){
    int N, K; cin >> N >> K;
    vector<pair<int, int>> X(N);
    for(int i=0;i<N;i++){
        string dir;
        cin >> X[i].first >> X[i].second >> dir;
        if(dir == "L") X[i].second = -X[i].second;
    }
    sort(X.begin(), X.end());
    double L = 0.0, R = 1e10;
    for(int _=0;_<100;_++){
        double mid = 0.5*(L+R);
        vector<pair<double, int>> vp(N);
        for(int i=0;i<N;i++){
            vp[i].first = X[i].first + mid * X[i].second;
            vp[i].second = i;
        }
        sort(vp.begin(), vp.end());
        vector<int> idx(N);
        for(int i=0;i<N;i++) idx[i] = vp[i].second;
        if(LIS(idx) >= N-K) L = mid;
        else R = mid;
    }
    if(L > 2e9){
        printf("Infinity\n");
    } else {
        printf("%.10lf\n", 0.5*(L+R));
    }
}
