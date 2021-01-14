#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 998244353;

int bitCount(int t){
    int res = 0;
    for(int i=t;i;i&=i-1) ++res;
    return res;
}

void zetaTransform(vector<long long>& v, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<v.size();j++){
            if(j&(1<<i)) v[j] = (v[j] + v[j^(1<<i)]) % MOD;
        }
    }
}

void mobiusTransform(vector<long long>& v, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<v.size();j++){
            if(j&(1<<i)) v[j] = (v[j] + MOD - v[j^(1<<i)]) % MOD;
        }
    }
}

vector<long long> subsetConvolutionSqrt(const vector<long long>& a, int n){
    auto zeta = [&](const vector<long long>& v){
        vector<vector<long long>> res(n+1, vector<long long>(1<<n, 0));
        for(int i=0;i<(1<<n);i++) res[bitCount(i)][i] = v[i];
        for(auto& r : res) zetaTransform(r, n);
        return res;
    };
    auto az = zeta(a);
    vector<vector<long long>> cz(n+1, vector<long long>(1<<n, 0));
    const auto inv2 = (MOD - MOD/2);
    for(int i=0;i<(1<<n);i++){
        cz[0][i] = 1;
        for(int j=1;j<=n;j++){
            cz[j][i] = az[j][i];
            for(int k=1;k<j;k++) cz[j][i] = (cz[j][i] + MOD - (cz[k][i] * cz[j-k][i]) % MOD) % MOD;
            cz[j][i] = (cz[j][i] * inv2) % MOD;
        }
    }
    for(auto& v : cz) mobiusTransform(v, n);
    vector<long long> res(1<<n, 0);
    for(int i=0;i<res.size();i++) res[i] = cz[bitCount(i)][i];
    return res;
}

int main(){
    int N; cin >> N;
    string L, R; cin >> L >> R;
    vector<long long> f(1 << N, 0);
    f[0] = 1;
    for(int i=1;i<L.size();i++) if(L[i] == '1') f[i] = MOD - 2;
    auto g = subsetConvolutionSqrt(f, N);
    long long res = 0;
    for(int i=1;i<R.size();i++){
        if(R[i] == '1') res = (res + MOD - g[i]) % MOD;
    }
    // vector<long long> dp(1<<N, 0);
    // for(int i=0;i<L.size();i++) dp[i] = L[i]-'0';
    // for(int i=0;i<(1<<N);i++){
    //     for(int j=i;(j^i)<j;j=(j-1)&i){
    //         dp[i] += dp[j]*dp[j^i];
    //         dp[i] %= MOD;
    //     }
    // }
    // long long res = 0;
    // for(int i=0;i<R.size();i++){
    //     if(R[i] == '1') res += dp[i];
    // }
    cout << res%MOD << endl;
}