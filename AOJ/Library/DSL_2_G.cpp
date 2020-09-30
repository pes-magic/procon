#include <iostream>
#include <vector>

using namespace std;

template<typename M>
class LazySegTree {
public:
    using T = typename M::T;
    using F = typename M::F;
    using W = typename M::W;
    explicit LazySegTree(int n)
        : cHeight(calcH_(n)), N(1 << cHeight)
        , mVal(2*N, M::def()), mLazy(N, M::unit()), mWidth(2*N, 1)
    {
        for(int i=N-1;i>0;i--) mWidth[i] = mWidth[2*i] + mWidth[2*i+1];
    }
    explicit LazySegTree(int n, T init) : LazySegTree(n) {
        for(int i=0;i<n;i++) mVal[N+i] = init;
        for(int i=N-1;i>0;i--) update_(i);
    }
    explicit LazySegTree(const vector<T>& init) : LazySegTree(init.size()) {
        for(int i=0;i<init.size();i++) mVal[N+i] = init[i];
        for(int i=N-1;i>0;i--) update_(i);
    }
    void setWidth(const vector<W>& w){
        for(int i=0;i<w.size();i++) mWidth[N+i] = w[i];
        for(int i=N-1;i>0;i--) mWidth[i] = mWidth[2*i] + mWidth[2*i+1];
    }
    void update(int l, int r, F value){
        l = max(0, l) + N;
        r = min(N, r) + N;
        int hl = cHeight;
        int hr = cHeight;
        while(hl && (l>>hl)<<hl != l){ push_(l>>hl); --hl; }
        while(hr && (r>>hr)<<hr != r){ push_((r-1)>>hr); --hr; }
        int l2 = l, r2 = r;
        while(l2 < r2){
            if(l2&1){ apply_(l2, value); l2++; }
            if(r2&1){ apply_(r2-1, value); }
            l2 /= 2;
            r2 /= 2;
        }
        for(int i=hl+1;i<=cHeight;i++) update_(l>>i);
        for(int i=hr+1;i<=cHeight;i++) update_((r-1)>>i);
    }
    T get(int l, int r){
        l = max(0, l) + N;
        r = min(N, r) + N;
        for(int i=cHeight;i && (l>>i)<<i != l;i--) push_(l>>i);
        for(int i=cHeight;i && (r>>i)<<i != r;i--) push_((r-1)>>i);
        T resL = M::def();
        T resR = M::def();
        while(l < r){
            if(l&1){ resL = M::operate(resL, mVal[l]); ++l; }
            if(r&1){ resR = M::operate(mVal[r-1], resR); }
            l /= 2;
            r /= 2;
        }
        return M::operate(resL, resR);
    }
private:
    int calcH_(int n){
        int res = 1;
        while((1 << res) < n) ++res;
        return res;
    }
    inline void push_(int idx){
        apply_(2*idx, mLazy[idx]);
        apply_(2*idx+1, mLazy[idx]);
        mLazy[idx] = M::unit();
    }
    inline void apply_(int idx, const F& value){
        M::applyFunc(mVal[idx], value, mWidth[idx]);
        if(idx < N) M::mulFunc(value, mLazy[idx]);
    }
    inline void update_(int idx){
        mVal[idx] = M::operate(mVal[2*idx], mVal[2*idx+1]);
    }
    const int cHeight;
    const int N;
    vector<W> mWidth;
    vector<T> mVal;
    vector<F> mLazy;
};

// range-add and range-sum-query
class RASQ {
public:
    using T = long long;
    using F = long long;
    using W = int;
    static constexpr T default_value = 0;
    static constexpr F unit_op = 0;
    static const T def() { return default_value; }
    static const F unit() { return unit_op; }
    static T operate(const T& a, const T& b){ return a + b; }
    static void mulFunc(F f, F& cur){ cur += f; }
    static void applyFunc(T& val, const F& op, W width){ val += op * width; }
};

int main(){
    int n, q;
    while(cin >> n >> q){
        LazySegTree<RASQ> seg(n);
        for(int i=0;i<q;i++){
            int t; cin >> t;
            if(t == 0){
                int s, t, x; cin >> s >> t >> x;
                seg.update(s-1, t, x);
            } else {
                int s, t; cin >> s >> t;
                cout << seg.get(s-1, t) << endl;
            }
        }
    }
}
