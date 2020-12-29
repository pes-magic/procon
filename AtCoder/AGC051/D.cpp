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

vector<long long> convolution(const vector<long long>& a, const vector<long long>& b){
    int _n = a.size() + b.size();
    int n = 1;
    while(n < _n) n *= 2;
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

int main(){
    const int maxSize = 1000001;
    vector<long long> inv(maxSize);
    vector<long long> fact(maxSize);
    vector<long long> factInv(maxSize);
    for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
    for(int i=2;i<maxSize;i++){
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
        fact[i] = fact[i-1] * i % MOD;
        factInv[i] = factInv[i-1] * inv[i] % MOD;
    }
    auto comb = [&](int n, int r){
        if(n < r || r < 0) return 0LL;
        return fact[n] * factInv[n-r] % MOD * factInv[r] % MOD;
    };
    int a, b, c, d; cin >> a >> b >> c >> d;
    if(a%2 != b%2 || b%2 != c%2 || c%2 != d%2){
        cout << 0 << endl;
        return 0;
    }
    long long res = 0;
    vector<long long> va(a/2+1, 0);
    vector<long long> vb(d/2+1, 0);
    vector<long long> sum(a/2+d/2+1, 0);
    for(int i=0;2*i<=a;i++){
        if((b-a)/2+i < 0) continue;
        va[i] = factInv[i] * factInv[a-2*i] % MOD * factInv[(b-a)/2+i] % MOD;
    }
    for(int i=0;2*i<=d;i++){
        if((c-d)/2+i < 0) continue;
        vb[i] = factInv[i] * factInv[d-2*i] % MOD * factInv[(c-d)/2+i] % MOD;
    }
    for(int i=0;i<sum.size();i++){
        if((b-a+c-d)/2+i < 0) continue;
        sum[i] = fact[i] * fact[a+d-2*i] % MOD * fact[(b-a+c-d)/2+i] % MOD;
        sum[i] *= comb((b+c)/2 - 1, (a+d)/2-i-1);
        sum[i] %= MOD;
        sum[i] *= comb((a+d)/2, i);
        sum[i] %= MOD;
    }
    auto v = convolution(va, vb);
    for(int i=0;i<sum.size();i++) res = (res + sum[i] * v[i]) % MOD;
    cout << res << endl;
}
