#include <iostream>
#include <vector>
#include <string>

using namespace std;

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
    void update_(T& data, T val) { data = val; }
    T operate(T a, T b) { return a+b; }
    const int N;
    const T def;
    vector<T> mVal;
};

int main(){
    int N, K; cin >> N >> K;
    string S; cin >> S;
    SegTree<int> seg(N+K+1, 0);
    for(int i=N;i<=N+K;i++) seg.update(i, 1);
    for(int i=N-1;i>0;i--){
        if(S[i-1] == 'x' || seg.get(i+1, i+K+1) < K) seg.update(i, 1);
    }
    if(seg.get(1, K+1) == K){
        cout << 0 << endl;
    } else {
        for(int i=1;i<=K;i++) if(!seg.get(i, i+1)) cout << i << endl;
    }
}