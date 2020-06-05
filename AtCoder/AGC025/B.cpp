#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main(){
    const int maxSize = 300001;
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
    long long N, A, B, K; cin >> N >> A >> B >> K;
    long long res = 0;
    for(int i=0;i<=N;i++){
        if(K - A*i < 0) break;
        if((K - A*i)%B != 0) continue;
        int j = (K - A*i)/B;
        res += comb(N, i) * comb(N, j);
        res %= MOD;
    }
    cout << res << endl;
}