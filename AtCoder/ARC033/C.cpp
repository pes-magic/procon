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
    T operate(T a, T b) { return a+b; }
    const int N;
    const T def;
    vector<T> mVal; 
};

int main(){
    int Q;
    while(cin >> Q){
        SegTree<int> seg(200001, 0);
        for(int i=0;i<Q;i++){
            int T, X; cin >> T >> X;
            if(T == 1){
                seg.update(X, 1);
            } else {
                int L = 0, R = 200001;
                while(R-L > 1){
                    int mid = (L+R)/2;
                    int sum = seg.get(0, mid);
                    if(sum < X) L = mid;
                    else R = mid;
                }
                cout << L << endl;
                seg.update(L, 0);
            }
        }
    }
}