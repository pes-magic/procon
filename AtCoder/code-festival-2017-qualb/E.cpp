#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    const int maxSize = 2020;
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
    int A, B; cin >> A >> B;
    long long res = 1;
    for(int c1=1;c1<=B;c1++){
        int restA = A - (B-c1);
        if(c1 == B) --restA;
        res += comb(restA+1, 1) * comb(B-1, c1-1);
        res %= MOD;
        for(int c2=1;c1+c2<=B;c2++){
            int restA = A - (B-c1) - (B-c1-c2);
            if(c1 + c2 == B) --restA;
            res += comb(restA+2, 2) * comb(B-1, c1-1) % MOD * comb(B-c1-1, c2-1);
            res %= MOD;
        }
    }
    cout << res << endl;
}