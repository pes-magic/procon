#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

int main(){
    const int maxSize = 100001;
    vector<long long> inv(maxSize);
    vector<long long> fact(maxSize);
    vector<long long> factInv(maxSize);
    vector<long long> pow2(maxSize);
    for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
    for(int i=2;i<maxSize;i++){
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
        fact[i] = fact[i-1] * i % MOD;
        factInv[i] = factInv[i-1] * inv[i] % MOD;
    }
    pow2[0] = 1;
    for(int i=1;i<maxSize;i++) pow2[i] = (pow2[i-1] * 2) % MOD;
    auto comb = [&](int n, int r){
        if(n < r || r < 0) return 0LL;
        return fact[n] * factInv[n-r] % MOD * factInv[r] % MOD;
    };
    auto perm = [&](int n, int r){
        if(n < r || r < 0) return 0LL;
        return fact[n] * factInv[n-r] % MOD;
    };
    int x, y;
    while(cin >> x >> y){
        long long res = 0;
        if(x > 4000 || y > 4000){
            cout << 0 << endl;
        }
        for(int i=0;i<=min(x, y);i++){
            int a = x-i;
            int b = y-i;
            for(int j=0;j<=min(a, b);j++){
                int ab = a-j;
                int ba = b-j;
                int aa = j;
                res += comb(ab+ba, ab) * comb(ab+ba+aa, aa) % MOD * pow2[aa] % MOD;
                res %= MOD;
            }
        }
        cout << res << endl;
    }
}