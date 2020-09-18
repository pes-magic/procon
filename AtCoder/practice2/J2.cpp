#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class SegTree {
public:
    explicit SegTree(int n, T def) : actualN(n), N(calcN_(n)), def(def), mVal(2*calcN_(n), def) {}
    void update(int idx, T value){
        int i = N + idx;
        update_(mVal[i], value);
        for(int t=i/2;t>=1;t/=2){
            mVal[t] = operate(mVal[2*t], mVal[2*t+1]);
        }
    }
    T get(int l, int r){
        l = max(0, l) + N;
        r = min(N, r) + N;
        T resL = def;
        T resR = def;
        while(l < r){
            if(l&1){ resL = operate(resL, mVal[l]); l++; }
            if(r&1){ resR = operate(mVal[r-1], resR); }
            l /= 2;
            r /= 2;
        }
        return operate(resL, resR);
    }
    template<class F>
    int maxRight(int l, F f){
        l = max(0, l) + N;
        T resL = def;
        while(l){
            if(l&1){
                T next = operate(resL, mVal[l]);
                if(f(next)){
                    while(l < N){
                        l *= 2;
                        next = operate(resL, mVal[l]);
                        if(!f(next)){
                            resL = next;
                            ++l;
                        }
                    }
                    return l - N;
                }
                resL = next;
                if(!(l&(l+1))) break;
                l++;
            }
            l /= 2;
        }
        return actualN;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void update_(T& data, T val) { data = val; }
    T operate(T a, T b) { return max(a, b); }
    const int N;
    const int actualN;
    const T def;
    vector<T> mVal;
};

int main(){
    int N, Q; cin >> N >> Q;
    SegTree<int> seg(N, 0);
    for(int i=0;i<N;i++){
        int a; cin >> a;
        seg.update(i, a);
    }
    for(int i=0;i<Q;i++){
        int t, x, v; cin >> t >> x >> v;
        if(t==1){
            seg.update(x-1, v);
        } else if(t==2){
            cout << seg.get(x-1, v) << endl;
        } else {
            cout << seg.maxRight(x-1, [&](int t){ return t >= v; }) + 1 << endl;
        }
    }
}