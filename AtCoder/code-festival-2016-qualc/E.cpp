#include <iostream>
#include <vector>

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
        T resL = def;
        T resR = def;
        while(offset > 0){
            if(l >= r) break;
            if(l&1){ resL = operate(resL, mVal[offset+l-1]); l++; }
            if(r&1){ resR = operate(mVal[offset+r-2], resR); }
            l /= 2;
            r /= 2;
            offset /= 2;
        }
        return operate(resL, resR);
    }
private:
    int calcN_(int n){
        int res = 1;
        while(res < n) res *= 2;
        return res;
    }
    void update_(T& data, T val) { data = val; }
    T operate(T a, T b) { return a+b; }
    const int N;
    const T def;
    vector<T> mVal;
};

int main(){
    int N; cin >> N;
    vector<long long> fact(N+1);
    fact[0] = fact[1] = 1;
    for(int i=2;i<=N;i++) fact[i] = fact[i-1] * i % MOD;
    const long long inv2 = MOD - MOD/2;
    vector<int> a(N);
    vector<int> forget(N+1, 1);
    int forgetSum = 0;
    for(auto& t : a){
        cin >> t;
        forget[t] = 0;
        --t;
    }
    for(int i=0;i<N;i++) if(forget[i+1]) forgetSum = (forgetSum + i) % MOD;
    for(int i=0;i<N;i++) forget[i+1] += forget[i];
    const int M = forget.back();
    long long res = fact[M];
    long long dec = 0;
    int cnt = 0;
    SegTree<int> seg(N, 0);
    for(int i=0;i<N;i++){
        if(a[i] == -1){
            long long sum = forgetSum * fact[M-1] % MOD;
            sum = (sum + MOD - cnt * fact[M] % MOD * inv2 % MOD) % MOD;
            sum = (sum + MOD - dec) % MOD;
            res += sum * fact[N-1-i];
            res %= MOD;
            ++cnt;
        } else {
            long long sum = (a[i] - seg.get(0, a[i])) * fact[M] % MOD;
            long long less = forget[a[i]+1];
            sum = (sum + MOD - less * cnt % MOD * fact[M-1] % MOD) % MOD;
            res += sum * fact[N-1-i];
            res %= MOD;
            dec += (M-less) * fact[M-1];
            dec %= MOD;
            seg.update(a[i], 1);
        }
    }
    cout << res << endl;
}