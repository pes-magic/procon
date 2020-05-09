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

void ntt(vector<long long>& v, int inv){
    const int n = v.size();
    auto w = modPow(3, (MOD-1)/n);
    if(inv == -1) w = calcInv(w);
    int rev = 0;
    for(int i=1;i<n-1;i++){
        for(int j=n/2;j>(rev^=j);j/=2);
        if(i < rev) swap(v[i], v[rev]);
    }
    for(int m=1;m<n;m*=2){
        auto cur = 1;
        auto rot = modPow(w, n/(2*m));
        for(int i=0;i<m;i++){
            for(int j=i;j<n;j+=2*m){
                auto p = v[j];
                auto q = v[j+m] * cur % MOD;
                v[j] = (p + q) % MOD;
                v[j+m] = (p + MOD - q) % MOD;
            }
            cur = (cur * rot) % MOD;
        }
    }
}

int pow2N(int t){
    int res = 1;
    while(res < t) res *= 2;
    return res;
}

vector<long long> convolution(const vector<long long>& a, const vector<long long>& b){
    const int n = pow2N(a.size() + b.size());
    vector<long long> na(n, 0), nb(n, 0);
    for(int i=0;i<a.size();i++) na[i] = a[i];
    for(int i=0;i<b.size();i++) nb[i] = b[i];
    ntt(na, 1);
    ntt(nb, 1);
    for(int i=0;i<n;i++) na[i] = na[i] * nb[i] % MOD;
    ntt(na, -1);
    auto inv = calcInv(n);
    for(int i=0;i<n;i++) na[i] = na[i] * inv % MOD;
    return na;
}

int getCost(int a){
    for(int i=0;;i++){
        if(a%(1<<i)) return i;
    }
    return -1;
}

void solve(int begin, int end, vector<long long>& path, vector<long long>& cost, const vector<int>& jump, const vector<int>& valid){
    const int n = end - begin;
    if(n == 1) return;
    solve(begin, begin+n/2, path, cost, jump, valid);
    vector<long long> p(n/2), c(n/2), j(n);
    for(int i=0;i<n/2;i++){
        p[i] = path[i+begin];
        c[i] = cost[i+begin];
    }
    for(int i=0;i<n;i++) j[i] = jump[i];
    auto cp = convolution(p, j);
    auto cc = convolution(c, j);
    const int cur = getCost(begin+n/2);
    for(int i=0;i<n/2;i++){
        if(!valid[begin+n/2+i]) continue;
        path[begin+n/2+i] += cp[n/2-1+i];
        path[begin+n/2+i] %= MOD;
        cost[begin+n/2+i] += cc[n/2-1+i] + cp[n/2-1+i] * cur;
        cost[begin+n/2+i] %= MOD;
    }
    solve(begin+n/2, end, path, cost, jump, valid);
}

int main(){
    int N, K, M; cin >> N >> K >> M;
    const int N2 = pow2N(N+1);
    vector<int> jump(N2, 0);
    vector<int> valid(N2, 1);
    vector<long long> path(N2, 0);
    vector<long long> cost(N2, 0);
    path[1] = 1;
    for(int i=0;i<K;i++){
        int b; cin >> b;
        valid[b] = 0;
    }
    for(int i=0;i<M;i++){
        int d; cin >> d;
        jump[d-1] = 1;
    }
    solve(0, N2, path, cost, jump, valid);
    cout << cost[N] << endl;
}