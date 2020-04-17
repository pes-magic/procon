#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>

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
    T operate(T a, T b) { return make_pair(a.first * b.first, a.second * b.first + b.second); }
    const int N;
    const T def;
    vector<T> mVal;
};

int main(){
    long long N;
    int M;
    while(cin >> N >> M){
        vector<long long> p(M);
        vector<double> a(M), b(M);
        for(int i=0;i<M;i++){
            cin >> p[i] >> a[i] >> b[i];
        }
        auto ps = p;
        sort(ps.begin(), ps.end());
        ps.erase(unique(ps.begin(), ps.end()), ps.end());
        map<long long, int> idx;
        for(int i=0;i<ps.size();i++) idx[ps[i]] = i;
        SegTree<pair<double, double>> seg(ps.size(), make_pair(1.0, 0.0));
        double low = 1.0, high = 1.0;
        for(int i=0;i<M;i++){
            seg.update(idx[p[i]], make_pair(a[i], b[i]));
            auto pr = seg.get(0, ps.size());
            auto cur = pr.first + pr.second;
            low = min(low, cur);
            high = max(high, cur);
        }
        printf("%.12lf\n%.12lf\n", low, high);
    }
}