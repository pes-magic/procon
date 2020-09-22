#include <iostream>
#include <vector>

using namespace std;

struct Node {
    Node(int z=0, int o=0, long long i=0) : zero(z), one(o), inv(i){}
    int zero, one;
    long long inv;
};

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
        T v = operate_(a, b);
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
    inline T operate_(const T& a, const T& b) const {
        return T(a.zero + b.zero, a.one + b.one, a.inv + b.inv + (long long)a.one * b.zero);;
    }
    inline void mulFunc_(F f, F& cur){ if(f) cur = 1 - cur; }
    inline void applyFunc_(int idx){
        if(!mLazy[idx]) return;
        const long long n = mVal[idx].zero + mVal[idx].one;
        swap(mVal[idx].zero, mVal[idx].one);
        mVal[idx].inv = n*(n-1)/2 - mVal[idx].inv - mVal[idx].zero*(mVal[idx].zero-1)/2 - mVal[idx].one*(mVal[idx].one-1)/2;
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
    vector<Node> a(N, Node(0, 0, 0));
    for(int i=0;i<N;i++){
        int t; cin >> t;
        if(t == 0) a[i].zero = 1;
        else a[i].one = 1;
    }
    LazySegTree<Node, int> seg(N, a, Node(0, 0, 0), 0);
    for(int i=0;i<Q;i++){
        int t, l, r; cin >> t >> l >> r;
        if(t == 1){
            seg.update(l-1, r, true);
        } else {
            cout << seg.get(l-1, r).inv << endl;
        }
    }
}