#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    const int maxSize = 600002;
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
    auto perm = [&](int n, int r){
        if(n < r || r < 0) return 0LL;
        return fact[n] * factInv[n-r] % MOD;
    };
    long long N, M, L, R; cin >> N >> M >> L >> R;
    long long all = (comb(N+R, R) + MOD - comb(N+L-1, L-1)) % MOD;
    vector<long long> base(R+1, 0);
    for(int i=0;i<=N-M && i+M <= R;i++){
        long long add = comb(N-M, i);
        if(i%2) add = (MOD - add) % MOD;
        for(int j=1;j*(i+M)<=R;j++) base[j*(i+M)] = (base[j*(i+M)] + add) % MOD;
    }
    vector<long long> pre(R+1, 0);
    for(int i=0;i<=R;i++){
        long long add = comb(N+i, i);
        pre[i] = (pre[i] + add) % MOD;
        if(i+M <= R) pre[i+M] = (pre[i+M] + MOD - add) % MOD;
    }
    long long sub = 0;
    for(int i=0;i<=L-1;i++) sub = (sub + MOD - (base[i] * pre[L-1-i]) % MOD) % MOD;
    for(int i=0;i<=R;i++) sub = (sub + base[i] * pre[R-i]) % MOD;
    sub = (sub * comb(N, M)) % MOD;
    cout << (all + MOD - sub) % MOD << endl;
}