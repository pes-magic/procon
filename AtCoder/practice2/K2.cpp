#include <iostream>
#include <vector>

using namespace std;

// ax+b -> c(ax+b) + d = acx + bc + d

const int MOD = 998244353;

template<typename T, typename F, typename W = int>
class LazySegTree {
public:
    explicit LazySegTree(int n, T def, F unit)
        : N(calcN_(n)), def(def), unit(unit)
        , mVal(2*calcN_(n), def), mLazy(2*calcN_(n), unit), mWidth(2*calcN_(n), 1)
    {
        for(int i=N-2;i>=0;i--) mWidth[i] = mWidth[2*i+1] + mWidth[2*i+2];
    }
    explicit LazySegTree(int n, T init, T def, F unit) : LazySegTree(n, def, unit) {
        for(int i=0;i<n;i++) mVal[N-1+i] = init;
        for(int i=N-2;i>=0;i--) mVal[i] = operate_(mVal[2*i+1], mVal[2*i+2]);
    }
    explicit LazySegTree(int n, vector<T> init, T def, F unit) : LazySegTree(n, def, unit) {
        for(int i=0;i<n;i++) mVal[N-1+i] = init[i];
        for(int i=N-2;i>=0;i--) mVal[i] = operate_(mVal[2*i+1], mVal[2*i+2]);
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
        eval_(idx, rangeL, rangeR);
        if(r <= rangeL || rangeR <= l) return;
        if(l <= rangeL && rangeR <= r){
            setLazy_(idx, value);
            eval_(idx, rangeL, rangeR);
        } else {
            int rangeM = (rangeL+rangeR)/2;
            updateImpl_(l, r, value, 2*idx+1, rangeL, rangeM);
            updateImpl_(l, r, value, 2*idx+2, rangeM, rangeR);
            mVal[idx] = operate_(mVal[2*idx+1], mVal[2*idx+2]);
        }
    }
    inline void setLazy_(int idx, F value){
        mulFunc_(value, mLazy[idx]);
    }
    T getImpl_(int l, int r, int idx, int rangeL, int rangeR){
        if(r <= rangeL || rangeR <= l) return def;
        eval_(idx, rangeL, rangeR);
        if(l <= rangeL && rangeR <= r) return mVal[idx];
        int rangeM = (rangeL+rangeR)/2;
        T a = getImpl_(l, r, 2*idx+1, rangeL, rangeM);
        T b = getImpl_(l, r, 2*idx+2, rangeM, rangeR);
        return operate_(a, b);
    }
    void eval_(int idx, int rangeL, int rangeR){
        applyFunc_(idx);
        if(idx < N - 1){
            setLazy_(2*idx+1, mLazy[idx]);
            setLazy_(2*idx+2, mLazy[idx]);
        }
        mLazy[idx] = unit;
    }
    inline T operate_(T a, T b) const { return (a + b) % MOD; }
    inline void mulFunc_(F f, F& cur){
        cur.first = (cur.first * f.first) % MOD;
        cur.second = (cur.second * f.first + f.second) % MOD;
    }
    inline void applyFunc_(int idx){
        mVal[idx] = (mLazy[idx].first * mVal[idx] + mWidth[idx] * mLazy[idx].second) % MOD;
    }
    const int N;
    const T def;
    const F unit;
    vector<W> mWidth;
    vector<T> mVal;
    vector<F> mLazy;
};

int main(){
    int N, Q; cin >> N >> Q;
    vector<long long> a(N);
    for(auto& t : a) cin >> t;
    LazySegTree<long long, pair<long long, long long>> seg(N, a, 0, make_pair(1, 0));
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