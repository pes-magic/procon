#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const long long INF = 1LL << 60;

template<typename T>
class SegTree {
public:
    explicit SegTree(int n, T def) : N(calcN_(n)), def(def), mVal(2*calcN_(n)-1, def) {}
    void update(int idx, T value){
        int i = N + idx - 1;
        update_(mVal[i], value);
        while(i > 0){
            i = (i-1)/2;
            mVal[i] = operate(mVal[2*i+1], mVal[2*i+2]);
        }
    }
    T get(int l, int r){
        l = max(0, l);
        r = min(N, r);
        int offset = N;
        T resL = def;
        T resR = def;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ resL = operate(resL, mVal[offset+l-1]); l++; }
            if(r&1){ resR = operate(mVal[offset+r-2], resR); }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
        return operate(resL, resR);
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void update_(T& data, T val) { data = min(data, val); }
    T operate(T a, T b) { return min(a, b); }
    const int N;
    const T def;
    vector<T> mVal;
};

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N, M; cin >> N >> M;
        vector<long long> C(N);
        for(auto& c : C) cin >> c;
        SegTree<long long> seg(N, INF);
        seg.update(0, 0);
        for(int i=1;i<N-1;i++){
            if(C[i] > 0){
                seg.update(i, seg.get(max(0, i-M), i) + C[i]);
            }
        }
        auto res = seg.get(max(0, N-M-1), N-1);
        printf("Case #%d: %lld\n", t, res < INF ? res : -1);
    }
}