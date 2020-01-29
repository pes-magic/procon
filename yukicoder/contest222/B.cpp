#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class RangeAddQuery {
public:
    explicit RangeAddQuery(int n) : N(calcN_(n)) {
        mVal.assign(2*N+1, 0);
    }
    void update(int l, int r, T value){
        updateImpl_(l, r, value, 0, 0, N);
    }
    T get(int idx){
        int i = N + idx - 1;
        auto res = mVal[i];
        while(i > 0){
            i = (i-1)/2;
            res += mVal[i];
        }
        return res;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void updateImpl_(int l, int r, T value, int idx, int rangeL, int rangeR){
        if(r <= rangeL || rangeR <= l) return;
        if(l <= rangeL && rangeR <= r){
            mVal[idx] += value;
        } else {
            int rangeM = (rangeL+rangeR)/2;
            updateImpl_(l, r, value, 2*idx+1, rangeL, rangeM);
            updateImpl_(l, r, value, 2*idx+2, rangeM, rangeR);
        }
    }
    const int N;
    vector<T> mVal; 
};


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
        return getImpl_(l, r, 0, 0, N);
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    T getImpl_(int l, int r, int idx, int rangeL, int rangeR){
        if(r <= rangeL || rangeR <= l) return def;
        if(l <= rangeL && rangeR <= r) return mVal[idx];
        int rangeM = (rangeL+rangeR)/2;
        T a = getImpl_(l, r, 2*idx+1, rangeL, rangeM);
        T b = getImpl_(l, r, 2*idx+2, rangeM, rangeR);
        return operate(a, b);
    }
    void update_(T& data, T val) { data = val; }
    T operate(T a, T b) { return a+b; }
    const int N;
    const T def;
    vector<T> mVal; 
};

int main(){
    int N, Q; cin >> N >> Q;
    vector<int> a(N);
    for(auto& t : a) cin >> t;
    RangeAddQuery<int> raq(N+1);
    SegTree<int> seg(N+1, 0);
    for(int i=0;i<N;i++) raq.update(i+1, i+2, a[i]);
    for(int i=0;i+1<N;i++){
        if(a[i] != a[i+1]) seg.update(i+1, 1);
    }
    for(int q=0;q<Q;q++){
        int t, l, r; cin >> t >> l >> r;
        if(t == 1){
            int x; cin >> x;
            raq.update(l, r+1, x);
            if(l >= 2){
                seg.update(l-1, raq.get(l-1) != raq.get(l) ? 1 : 0);
            }
            if(r+1 <= N){
                seg.update(r, raq.get(r) != raq.get(r+1) ? 1 : 0);
            }
        } else {
            cout << seg.get(l, r) + 1 << endl;
        }
    }
}