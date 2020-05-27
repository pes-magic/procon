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
    int N, M; cin >> N >> M;
    long long res = 0;
    for(int m=0;2*m<=M;m++){
        int m2 = M + m;
        int m1 = M - 2*m;
        if(m1 > N) continue;
        res = (res + comb(m2+N-1, N-1) * comb(N, m1)) % MOD;
        if(m1 > 0){
            res = (res + MOD - (comb(m2-M+N-2, N-2) * comb(N-1, m1-1)) % MOD * N % MOD) % MOD;
        }
        if(m2 >= M+1){
            res = (res + MOD - (comb(m2-M-1+N-1, N-1) * comb(N, m1)) % MOD * N % MOD) % MOD;
        }
    }
    cout << res << endl;
}