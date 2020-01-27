// 遅延評価セグメント木(区間更新+総和クエリ)
// Verifyed
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I

template<typename T>
class LazySegTree {
public:
    explicit LazySegTree(int n, T init, T def) : N(calcN_(n)), def(def) {
        mVal.assign(2*N+1, 0);
        update(0, N, init);
        mLazy.assign(2*N+1, 0);
        mDirty.assign(2*N+1, 0);
    }
    void update(int l, int r, T value){
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
    void updateImpl_(int l, int r, T value, int idx, int rangeL, int rangeR){
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
    void setLazy_(int idx, T value){
        mLazy[idx] = value;
        mDirty[idx] = 1;
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
        if(!mDirty[idx]) return;
        mVal[idx] = (rangeR - rangeL) * mLazy[idx];
        if(idx < N-1){
            setLazy_(2*idx+1, mLazy[idx]);
            setLazy_(2*idx+2, mLazy[idx]);
        }
        mLazy[idx] = 0;
        mDirty[idx] = 0;
    }
    T operate_(T a, T b) const { return a + b; }
    const int N;
    const T def;
    vector<T> mVal; 
    vector<T> mLazy;
    vector<int> mDirty;
};
