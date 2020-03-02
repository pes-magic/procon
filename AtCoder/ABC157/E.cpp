#include <iostream>
#include <vector>
#include <string>

using namespace std;

int bitCount(int t){
    int res = 0;
    for(int i=t;i;i&=i-1) ++res;
    return res;
}

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
    T operate(T a, T b) { return a|b; }
    const int N;
    const T def;
    vector<T> mVal; 
};

int main(){
    int N;
    while(cin >> N){
        string S; cin >> S;
        SegTree<unsigned int> seg(N, 0);
        for(int i=0;i<N;i++) seg.update(i, 1UL << (S[i]-'a'));
        int Q; cin >> Q;
        for(int i=0;i<Q;i++){
            int q; cin >> q;
            if(q == 1){
                int p; char c;
                cin >> p >> c;
                seg.update(p-1, (1UL << (c-'a')));
            } else {
                int l, r;
                cin >> l >> r;
                cout << bitCount(seg.get(l-1, r)) << endl;
            }
        }
    }
}
