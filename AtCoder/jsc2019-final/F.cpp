#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

struct Query {
    explicit Query(int l, int r, int block, int id) : l(l), r(r), block(block), id(id) {}
    int l, r, block, id;
    bool operator < (const Query& q) const { return block != q.block ? block < q.block : r < q.r; }
};

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

vector<int> mul(const vector<int>& ex, long long p1){
    auto res = ex;
    for(int i=0;i<ex.size()-1;i++) res[i+1] = (res[i+1] + ex[i] * p1) % MOD;
    return res;
}

vector<int> div(const vector<int>& ex, long long p1){
    if(p1 == 0) return ex;
    long long pInv = calcInv(p1);
    auto res = vector<int>(ex.size(), 0);
    long long sub = 0;
    for(int i=ex.size()-1;i>0;i--){
        long long m = (ex[i] + MOD - sub) * pInv % MOD;
        res[i-1] = m;
        sub = m;
    }
    return res;
}

int main(){
    int N, Q; cin >> N >> Q;
    vector<long long> fact(N+1);
    for(int i=0;i<2;i++) fact[i] = 1;
    for(int i=2;i<=N;i++) fact[i] = fact[i-1] * i % MOD;

    vector<int> A(N);
    for(auto& t : A) cin >> t;
    int sqN = 1;
    while(sqN*sqN < N) ++sqN;
    vector<Query> vq;
    for(int i=0;i<Q;i++){
        int l, r; cin >> l >> r;
        vq.emplace_back(l, r, l/sqN, i);
    }
    sort(vq.begin(), vq.end());
    int l = 0, r = 0;
    vector<int> res(Q, fact[N]);
    vector<int> ex(N+1, 0);
    ex[0] = 1;
    vector<int> cnt(N, 0);
    auto update = [&](int idx, int dif){
        ex = div(ex, cnt[idx]);
        cnt[idx] += dif;
        ex = mul(ex, cnt[idx]);
    };
    for(auto& q : vq){
        for(int i=r;i<q.r;i++) update(A[i], 1);
        for(int i=l-1;i>=q.l;i--) update(A[i], 1);
        for(int i=r-1;i>=q.r;i--) update(A[i], -1);
        for(int i=l;i<q.l;i++) update(A[i], -1);
        l = q.l;
        r = q.r;
        for(int i=1;i<=N;i++){
            res[q.id] = (res[q.id] + MOD + (i%2 ? -1 : 1) * (ex[i] * fact[N-i] % MOD)) % MOD;
        }
    }
    for(auto& t : res) cout << t << endl;
}
