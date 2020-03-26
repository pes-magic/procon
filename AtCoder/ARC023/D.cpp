#include <iostream>
#include <vector>
#include <map>

using namespace std;

int gcd(int a, int b){ return a%b ? gcd(b, a%b) : b; }

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
    int find(int l, int r, T value){
        return findImpl_(l, r, value, 0, 0, N);
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
    T findImpl_(int l, int r, T value, int idx, int rangeL, int rangeR){
        if(rangeR - rangeL == 1){
            return operate(value, mVal[idx]) == value ? rangeR : rangeL;
        }
        int rangeM = (rangeL+rangeR)/2;
        T a = getImpl_(l, r, 2*idx+1, rangeL, rangeM);
        if(operate(value, a) != value) return findImpl_(l, r, value, 2*idx+1, rangeL, rangeM);
        T b = getImpl_(l, r, 2*idx+2, rangeM, rangeR);
        if(operate(value, b) != value) return findImpl_(l, r, value, 2*idx+2, rangeM, rangeR);
        return r;
    }
    void update_(T& data, T val) { data = val; }
    T operate(T a, T b) { return !a ? b : !b ? a : gcd(a, b); }
    const int N;
    const T def;
    vector<T> mVal;
};

map<int, long long> solve(const vector<int>& a){
    const int n = a.size();
    SegTree<int> seg(n, 0);
    for(int i=0;i<n;i++) seg.update(i, a[i]);
    map<int, long long> res;
    for(int i=0;i<n;i++){
        int idx = i;
        int cur = a[i];
        while(idx < n){
            cur = gcd(cur, a[idx]);
            int end = seg.find(idx, n, cur);
            if(!res.count(cur)) res[cur] = 0;
            res[cur] += end - idx;
            idx = end;
        }
    }
    return res;
}

int main(){
    int n, m;
    while(cin >> n >> m){
        vector<int> a(n);
        for(auto& t : a) cin >> t;
        auto res = solve(a);
        for(int i=0;i<m;i++){
            int b; cin >> b;
            cout << res[b] << endl;
        }
    }
}