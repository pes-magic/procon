#include <iostream>
#include <vector>

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
    T operate(T a, T b) { return min(a, b); }
    const int N;
    const T def;
    vector<T> mVal; 
};

int main(){
    int N, Q; cin >> N >> Q;
    SegTree<pair<int,int>> seg(N+1, make_pair(N+1, N+1));
    for(int i=1;i<=N;i++){
        int a; cin >> a;
        seg.update(i, make_pair(a, i));
    }
    for(int i=0;i<Q;i++){
        int q, l, r; cin >> q >> l >> r;
        if(q == 1){
            int a = seg.get(l, l+1).first;
            int b = seg.get(r, r+1).first;
            seg.update(l, make_pair(b, l));
            seg.update(r, make_pair(a, r));
        } else {
            cout << seg.get(l, r+1).second << endl;
        }
    }
}