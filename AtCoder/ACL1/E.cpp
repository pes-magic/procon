#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

long long calcInv(long long a){
    return modPow(a, MOD-2);
}

struct Node {
    Node() : prod(0), invProd(0), num(0) {}
    Node(int p) : prod(p), invProd(calcInv(p)), num(1) {}
    Node(int p, int i, int n) : prod(p), invProd(i), num(n) {}
    int prod;
    int invProd;
    int num;
};

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
    T operate(T a, T b) { return Node((a.prod+b.prod)%MOD, (a.invProd+b.invProd)%MOD, a.num+b.num); }
    const int N;
    const T def;
    vector<T> mVal;
};

int main(){
    int N, K; cin >> N >> K;
    vector<int> pos(N);
    for(int i=0;i<N;i++){
        int p; cin >> p;
        pos[p-1] = i;
    }
    SegTree<Node> seg(N, Node());
    const auto half = calcInv(2);
    long long baseProd = (K-1LL) * calcInv(K) % MOD;
    long long res = 0;
    for(auto p : pos){
        long long base = modPow(baseProd, max(0, p+1-K));
        auto left = seg.get(0, p);
        res = res + base * left.invProd % MOD * half % MOD;
        auto right = seg.get(p, N);
        res = res + (right.num + MOD - right.prod * calcInv(base) % MOD * half % MOD);
        res %= MOD;
        seg.update(p, Node(base));
    }
    cout << res << endl;
}