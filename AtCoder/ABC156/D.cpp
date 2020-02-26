#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

int main(){
    const int maxSize = 200001;
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
    int n, a, b;
    while(cin >> n >> a >> b){
        long long res = (modPow(2, n) + MOD - 1) % MOD;
        auto calc = [&](int t){
            long long r = 1;
            for(int i=0;i<t;i++){
                r *= (n-i);
                r %= MOD;
                r *= inv[i+1];
                r %= MOD;
            }
            return r;
        };
        res = (res + MOD - calc(a)) % MOD;
        res = (res + MOD - calc(b)) % MOD;
        cout << res << endl;
    }
}