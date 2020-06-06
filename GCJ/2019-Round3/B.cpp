#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int MOD = 1000000007;

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
        l = max(0, l);
        r = min(N, r);
        int offset = N;
        T res = def;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ res = operate(res, mVal[offset+l-1]); l++; }
            if(r&1){ res = operate(res, mVal[offset+r-2]); }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
        return res;
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void update_(T& data, T val) { data = val; }
    T operate(T a, T b) { return max(a, b); }
    const int N;
    const T def;
    vector<T> mVal;
};

class Solver {
public:
    explicit Solver(int N) : res(0), p(N+2), sum(N+1), seg(N+1, make_pair(0, 0)) {
        sum[0] = 0;
        p[0] = p.back() = MOD;
        for(int i=1;i<=N;i++){
            cin >> p[i];
            sum[i] = sum[i-1] + p[i];
            seg.update(i, make_pair(p[i], i));
        }
        search_(1, N+1);
    }
    long long solve(){ return res; }
private:
    pair<long long, long long> search_(int begin, int end){
        if(end - begin <= 1) return make_pair(0, 0);
        auto p = seg.get(begin, end);
        long long highVal = p.first;
        auto highIdx = p.second;
        auto r1 = search_(begin, highIdx);
        auto r2 = search_(highIdx+1, end);
        res = (res + r1.first * (end - highIdx)) % MOD;
        res = (res + r2.second * (highIdx - begin + 1)) % MOD;
        auto r3 = make_pair((r1.first + r2.first) % MOD, (r1.second + r2.second) % MOD);
        auto restL = ((highIdx-begin) * highVal % MOD + MOD - (sum[highIdx-1] - sum[begin-1]) % MOD) % MOD;
        auto restR = ((end-1-highIdx) * highVal % MOD + MOD - (sum[end-1] - sum[highIdx]) % MOD) % MOD;
        r3.first = (r3.first + restR * (highIdx - begin + 1)) % MOD;
        r3.second = (r3.second + restL * (end - highIdx)) % MOD;
        return r3;
    }
private:
    long long res;
    vector<long long> p;
    vector<long long> sum;
    SegTree<pair<int, int>> seg;
};

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        int N; cin >> N;
        Solver solver(N);
        printf("Case #%d: %lld\n", t, solver.solve());
    }
}