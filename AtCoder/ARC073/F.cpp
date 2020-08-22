#include <iostream>
#include <vector>

using namespace std;

const long long INF = 1LL << 60;

template<typename T>
class LazySegTree {
public:
    explicit LazySegTree(int n, T init, T def) : N(calcN_(n)), def(def) {
        mVal.assign(2*N+1, init);
        mLazy.assign(2*N+1, 0);
        mDirty.assign(2*N+1, 0);
    }
    void update(int l, int r, T value){
        updateImpl_(l, r, value, 0, 0, N);
    }
    void setVal(int idx, T value){
        T cur= get(idx, idx+1);
        update(idx, idx+1, value - cur);
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
        eval_(idx);
        if(r <= rangeL || rangeR <= l) return;
        if(l <= rangeL && rangeR <= r){
            setLazy_(idx, value);
            eval_(idx);
        } else {
            int rangeM = (rangeL+rangeR)/2;
            updateImpl_(l, r, value, 2*idx+1, rangeL, rangeM);
            updateImpl_(l, r, value, 2*idx+2, rangeM, rangeR);
            mVal[idx] = operate_(mVal[2*idx+1], mVal[2*idx+2]);
        }
    }
    void setLazy_(int idx, T value){
        mLazy[idx] += value;
        mDirty[idx] = 1;
    }
    T getImpl_(int l, int r, int idx, int rangeL, int rangeR){
        if(r <= rangeL || rangeR <= l) return def;
        eval_(idx);
        if(l <= rangeL && rangeR <= r) return mVal[idx];
        int rangeM = (rangeL+rangeR)/2;
        T a = getImpl_(l, r, 2*idx+1, rangeL, rangeM);
        T b = getImpl_(l, r, 2*idx+2, rangeM, rangeR);
        return operate_(a, b);
    }
    void eval_(int idx){
        if(!mDirty[idx]) return;
        mVal[idx] += mLazy[idx];
        if(idx < N-1){
            setLazy_(2*idx+1, mLazy[idx]);
            setLazy_(2*idx+2, mLazy[idx]);
        }
        mLazy[idx] = 0;
        mDirty[idx] = 0;
    }
    T operate_(T a, T b) const { return min(a, b); }
    const int N;
    const T def;
    vector<T> mVal;
    vector<T> mLazy;
    vector<int> mDirty;
};

int main(){
    int N, Q, A, B; cin >> N >> Q >> A >> B;
    vector<int> x(Q);
    for(auto& t : x) cin >> t;
    LazySegTree<long long> minus(N+1, 1LL << 40, INF);
    LazySegTree<long long> plus(N+1, 1LL << 40, INF);
    minus.setVal(A, abs(B-x[0]) - A);
    minus.setVal(B, abs(A-x[0]) - B);
    plus.setVal(A, abs(B-x[0]) + A);
    plus.setVal(B, abs(A-x[0]) + B);
    for(int i=1;i<Q;i++){
        auto v = min(minus.get(0, x[i]) + x[i], plus.get(x[i], N+1) - x[i]);
        minus.update(1, N+1, abs(x[i]-x[i-1]));
        plus.update(1, N+1, abs(x[i]-x[i-1]));
        minus.setVal(x[i-1], v - x[i-1]);
        plus.setVal(x[i-1], v + x[i-1]);
    }
    long long res = INF;
    for(int i=1;i<=N;i++) res = min(res, plus.get(i, i+1) - i);
    cout << res << endl;
}