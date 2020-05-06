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
    int N; cin >> N;
    vector<long long> a(N), b(N);
    for(int i=0;i<N;i++){
        cin >> a[i] >> b[i];
    }
    auto res = convolution(a, b);
    cout << 0 << endl;
    for(int i=0;i<2*N-1;i++) cout << res[i] << endl;
}