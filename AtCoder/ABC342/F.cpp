#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

template<typename T>
class RangeAddQuery {
public:
    explicit RangeAddQuery(int n) : N(calcN_(n)) {
        mVal.assign(2*N+1, 0);
    }
    void update(int l, int r, T value){
        l = max(0, l);
        r = min(N, r);
        int offset = N;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ update_(mVal[offset+l-1], value); l++; }
            if(r&1){ update_(mVal[offset+r-2], value); }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
    }
    T get(int idx){
        int i = N + idx - 1;
        auto res = mVal[i];
        while(i > 0){
            i = (i-1)/2;
            update_(res, mVal[i]);
        }
        return res;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    inline void update_(T& data, T val) { data += val; }
    const int N;
    vector<T> mVal;
};

int main(){
    int N, L, D; cin >> N >> L >> D;
    RangeAddQuery<double> seg(N+D+1);
    seg.update(0, 1, 1);
    for(int i=0;i<L;i++){
        seg.update(i+1, i+D+1, seg.get(i)/D);
    }
    vector<double> win(N+1, 0);
    double total = 0.0;
    double lose = 0.0;
    for(int i=N;i>=0;i--){
        if(i >= L) lose += seg.get(i);
        double a = total/D;
        double b = 1.0 - lose;
        win[i] = max(a, b);
        total += win[i];
        if(i+D <= N) total -= win[i+D];
    }
    printf("%.10lf\n", win[0]);
}