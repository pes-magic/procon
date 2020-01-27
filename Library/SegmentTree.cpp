// セグメント木
// Verifyed
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
// https://atcoder.jp/contests/keyence2019/tasks/keyence2019_e
// https://atcoder.jp/contests/dwacon6th-prelims/tasks/dwacon6th_prelims_d
// https://yukicoder.me/problems/no/875

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
    void update_(T& data, T val) { data += val; }
    T operate(T a, T b) { return a+b; }
    const int N;
    const T def;
    vector<T> mVal; 
};
