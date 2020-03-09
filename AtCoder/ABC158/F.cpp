#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

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
    T operate(T a, T b) { return max(a, b); }
    const int N;
    const T def;
    vector<T> mVal; 
};

int main(){
    int N;
    while(cin >> N){
        vector<pair<int, int>> r(N);
        for(auto& p : r) cin >> p.first >> p.second;
        sort(r.begin(), r.end());
        SegTree<int> seg(N, 0);
        for(int i=0;i<N;i++) seg.update(i, i+1);
        int idx = N-1;
        for(auto it=r.end();it!=r.begin();){
            --it;
            auto v = distance(r.begin(), lower_bound(it, r.end(), make_pair(it->first + it->second, 0)));
            int next = seg.get(idx, v);
            seg.update(idx, next);
            --idx;
        }
        vector<int> dp(N+1, 0);
        dp[0] = 1;
        for(int i=0;i<N;i++){
            dp[i+1] = (dp[i+1] + dp[i]) % MOD;
            int next = seg.get(i, i+1);
            dp[next] = (dp[next] + dp[i]) % MOD;
        }
        cout << dp.back() << endl;
    }
}