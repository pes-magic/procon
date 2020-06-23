#include <iostream>
#include <vector>
#include <string>

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
    const int maxSize = 2000001;
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
    long long res = 0;
    int K; cin >> K;
    string S; cin >> S;
    const int N = S.size();
    for(int i=0;i<=K;i++){
        res += comb(i+N-1, N-1) * modPow(25, i) % MOD * modPow(26, K-i) % MOD;
        res %= MOD;
    }
    cout << res << endl;
}