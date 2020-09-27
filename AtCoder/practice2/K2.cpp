#include <iostream>
#include <vector>

using namespace std;

// ax+b -> c(ax+b) + d = acx + bc + d

const int MOD = 998244353;

template<typename M>
class LazySegTree {
public:
    using T = typename M::T;
    using F = typename M::F;
    using W = typename M::W;
    explicit LazySegTree(int n)
        : N(calcN_(n))
        , mVal(2*calcN_(n), M::def()), mLazy(2*calcN_(n), M::unit()), mWidth(2*calcN_(n), 1)
    {
        for(int i=N-2;i>=0;i--) mWidth[i] = mWidth[2*i+1] + mWidth[2*i+2];
    }
    explicit LazySegTree(int n, T init) : LazySegTree(n) {
        for(int i=0;i<n;i++) mVal[N-1+i] = init;
        for(int i=N-2;i>=0;i--) mVal[i] = M::operate(mVal[2*i+1], mVal[2*i+2]);
    }
    explicit LazySegTree(const vector<T>& init) : LazySegTree(init.size()) {
        for(int i=0;i<init.size();i++) mVal[N-1+i] = init[i];
        for(int i=N-2;i>=0;i--) mVal[i] = M::operate(mVal[2*i+1], mVal[2*i+2]);
    }
    void setWidth(const vector<W>& w){
        for(int i=0;i<w.size();i++) mWidth[N-1+i] = w[i];
        for(int i=N-2;i>=0;i--) mWidth[i] = mWidth[2*i+1] + mWidth[2*i+2];
    }
    void update(int l, int r, F value){
        updateImpl_(l, r, value, 0, 0, N);
    }
    T get(int l, int r){
        return getImpl_(l, r, 0, 0, N);
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void updateImpl_(int l, int r, F value, int idx, int rangeL, int rangeR){
        eval_(idx);
        if(r <= rangeL || rangeR <= l) return;
        if(l <= rangeL && rangeR <= r){
            setLazy_(idx, value);
            eval_(idx);
        } else {
            int rangeM = (rangeL+rangeR)/2;
            updateImpl_(l, r, value, 2*idx+1, rangeL, rangeM);
            updateImpl_(l, r, value, 2*idx+2, rangeM, rangeR);
            mVal[idx] = M::operate(mVal[2*idx+1], mVal[2*idx+2]);
        }
    }
    inline void setLazy_(int idx, F value){
        M::mulFunc(value, mLazy[idx]);
    }
    T getImpl_(int l, int r, int idx, int rangeL, int rangeR){
        if(r <= rangeL || rangeR <= l) return M::def();
        eval_(idx);
        if(l <= rangeL && rangeR <= r) return mVal[idx];
        int rangeM = (rangeL+rangeR)/2;
        T a = getImpl_(l, r, 2*idx+1, rangeL, rangeM);
        T b = getImpl_(l, r, 2*idx+2, rangeM, rangeR);
        return M::operate(a, b);
    }
    void eval_(int idx){
        M::applyFunc(mVal[idx], mLazy[idx], mWidth[idx]);
        if(idx < N - 1){
            setLazy_(2*idx+1, mLazy[idx]);
            setLazy_(2*idx+2, mLazy[idx]);
        }
        mLazy[idx] = M::unit();
    }
    const int N;
    vector<W> mWidth;
    vector<T> mVal;
    vector<F> mLazy;
};

class MONOID {
public:
    using T = long long;
    using F = pair<long long, long long>;
    using W = int;
    static constexpr T default_value = 0;
    static constexpr F unit_op = make_pair(1, 0);
    static const T def() { return default_value; }
    static const F unit() { return unit_op; }
    static T operate(T a, T b){ return (a + b) % MOD; }
    static void mulFunc(F f, F& cur){
        cur.first = (cur.first * f.first) % MOD;
        cur.second = (cur.second * f.first + f.second) % MOD;
    }
    static void applyFunc(T& val, const F& op, W width){
        val = (op.first * val + width * op.second) % MOD;
    }
};

int main(){
    int N, Q; cin >> N >> Q;
    vector<long long> a(N);
    for(auto& t : a) cin >> t;
    LazySegTree<MONOID> seg(a);
    for(int i=0;i<Q;i++){
        int t; cin >> t;
        if(t == 0){
            int l, r, b, c; cin >> l >> r >> b >> c;
            seg.update(l, r, make_pair(b, c));
        } else {
            int l, r; cin >> l >> r;
            cout << seg.get(l, r) << endl;
        }
    }
}