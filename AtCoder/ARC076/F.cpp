#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

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
    T operate_(T a, T b) const { return max(a, b); }
    const int N;
    const T def;
    vector<T> mVal;
    vector<T> mLazy;
    vector<int> mDirty;
};

int main(){
    int N, M; cin >> N >> M;
    const int INF = 1 << 30;
    LazySegTree<int> seg(M+2, 0, -INF);
    for(int i=1;i<=M;i++) seg.update(1, i+1, -1);
    int res = max(0, N-M);
    vector<pair<int, int>> vp;
    for(int i=0;i<N;i++){
        int L, R; cin >> L >> R;
        vp.emplace_back(L, R);
    }
    sort(vp.begin(), vp.end());
    for(auto& p : vp){
        seg.update(1, p.second+1, 1);
        res = max(res, seg.get(p.first+1, M+2) - p.first);
    }
    cout << res << endl;
}