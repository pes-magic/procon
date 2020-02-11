#include <iostream>
#include <vector>

using namespace std;

int gcd(int a, int b) { return a % b ? gcd(b, a % b) : b; }

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
    T operate(T a, T b) { return a && b ? gcd(a, b) : a ? a : b; }
    const int N;
    const T def;
    vector<T> mVal;
};

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

int main(){
    int N;
    while(cin >> N){
        RangeAddQuery<int> value(N);
        SegTree<int> diff(N - 1, 0);
        vector<int> a(N);
        for(auto& t : a) cin >> t;
        for (int i = 0; i < N;i++){
            value.update(i, i + 1, a[i]);
            if(i > 0) diff.update(i - 1, abs(a[i] - a[i - 1]));
        }
        int Q;
        cin >> Q;
        for (int i = 0; i < Q;i++){
            int t, l, r;
            cin >> t >> l >> r;
            --l;
            if(t){
                value.update(l, r, t);
                if(l > 0) diff.update(l - 1, abs(value.get(l) - value.get(l - 1)));
                if(r < N) diff.update(r - 1, abs(value.get(r) - value.get(r - 1)));
            } else {
                int t = value.get(l);
                int d = diff.get(l, r - 1);
                if(d) t = gcd(t, d);
                cout << t << endl;
            }
        }
    }
}