#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int MOD = 1000000007;

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
    auto perm = [&](int n, int r){
        if(n < r || r < 0) return 0LL;
        return fact[n] * factInv[n-r] % MOD;
    };
    long long H, W; cin >> H >> W;
    long long res = 0;
    int cycle = gcd(H, W);
    for(int i=1;i<cycle;i++){
        int j = cycle - i;
        if(lcm(lcm(i, H)/i, lcm(j, W)/j) == H*W/cycle){
            res = (res + comb(cycle, i)) % MOD;
        }
    }
    cout << res << endl;
}