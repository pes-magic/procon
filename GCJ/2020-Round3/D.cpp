#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

long long gcd(long long a, long long b){ return a%b ? gcd(b, a%b) : b; }

pair<long long, long long> solveSmall1(const vector<long long>& x, const vector<long long>& y, long long D){
    long long x0 = x[0] + y[0];
    long long y0 = x[0] - y[0];
    long long x1 = x[1] + y[1];
    long long y1 = x[1] - y[1];
    long long cx = 2 * D - abs(x0 - x1);
    long long cy = 2 * D - abs(y0 - y1);
    if(cx <= 0 || cy <= 0) return make_pair(0, 1);
    long long all = 8 * D * D - cx * cy;
    long long sub = 0;
    if(cx <= D || cy <= D){
        sub = 3 * cx * cy;
    } else {
        sub = all - 4 * (2 * D - cx) * (2 * D - cy);
    }
    auto g = gcd(sub, all);
    sub /= g;
    all /= g;
    return make_pair(sub, all);
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N; cin >> N;
        long long D; cin >> D;
        vector<long long> x(N), y(N);
        for(int i=0;i<N;i++) cin >> x[i] >> y[i];
        auto res = solveSmall1(x, y, D);
        printf("Case #%d: %lld %lld\n", t, res.first, res.second);
    }
}