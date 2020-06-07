#include <iostream>
#include <vector>

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
    int N; cin >> N;
    long long res = 0;
    long long sum = 0;
    long long p1 = (N-2)%2, p2 = (N-2)/2;
    while(p2 >= 0){
        long long ch = p1+p2+1;
        long long sel = comb(p1+p2, p1) * fact[ch] % MOD * fact[N-1-ch] % MOD;
        sel = (sel + MOD - sum) % MOD;
        res = (res + sel * ch) % MOD;
        sum = (sum + sel) % MOD;
        p1 += 2;
        --p2;
    }
    cout << res << endl;
}