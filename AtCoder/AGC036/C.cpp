#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

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
    auto perm = [&](int n, int r){
        if(n < r || r < 0) return 0LL;
        return fact[n] * factInv[n-r] % MOD;
    };
    int N, M;
    while(cin >> N >> M){
        long long res = (N * comb(M+N-2, N-2)) % MOD;
        long long sum = 0;
        for(int i=0;i<=M/2;i++){
            int m2 = M+i;
            long long cur = comb(m2+N-1, N-1);
            sum += N * comb(m2-M+N-2, N-2);
            sum %= MOD;
            cur = (cur + MOD - sum) % MOD;
            res += cur * comb(N, M-2*i);
            res %= MOD;
        }
        cout << res << endl;
    }
}