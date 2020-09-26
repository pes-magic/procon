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

void ntt2d(vector<vector<long long>>& v, int inv){
    for(auto& t : v) ntt(t, inv);
    vector<long long> m(v.size());
    for(int i=0;i<v[0].size();i++){
        for(int j=0;j<v.size();j++) m[j] = v[j][i];
        ntt(m, inv);
        for(int j=0;j<v.size();j++) v[j][i] = m[j];
    }
}

vector<vector<long long>> mul(const vector<vector<long long>>& a, const vector<vector<long long>>& b){
    auto res = a;
    for(int i=0;i<a.size();i++){
        for(int j=0;j<a[i].size();j++) res[i][j] = a[i][j] * b[i][j] % MOD;
    }
    return res;
}

vector<vector<long long>> pow(const vector<vector<long long>>& a, long long p){
    if(p == 1) return a;
    auto r = pow(a, p/2);
    r = mul(r, r);
    if(p%2 == 1) r = mul(r, a);
    return r;
}

int main(){
    int X, Y;
    while(cin >> X >> Y){
        long long T; cin >> T;
        int a, b, c, d; cin >> a >> b >> c >> d;
        int N = 1 << (X+1);
        int M = 1 << (Y+1);
        vector<vector<long long>> f(N, vector<long long>(M, 0LL));
        f[0][0] = f[0][1] = f[1][0] = f[N-1][0] = f[0][M-1] = 1;
        vector<vector<long long>> g(N, vector<long long>(M, 0LL));
        g[a][b] = g[N-a][M-b] = 1;
        g[a][M-b] = g[N-a][b] = MOD - 1;
        ntt2d(f, 1);
        ntt2d(g, 1);
        auto res = mul(pow(f, T), g);
        ntt2d(res, -1);
        cout << res[c][d] * calcInv(N*M) % MOD << endl;
    }
}