#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

int main(){
    vector<long long> inv(1000001);
	vector<long long> fact(1000001);
	vector<long long> factInv(1000001);
	for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
	for(int i=2;i<inv.size();i++){
		inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		fact[i] = fact[i-1] * i % MOD;
		factInv[i] = factInv[i-1] * inv[i] % MOD;
	}
	auto comb = [&](int n, int r){
		if(n < r) return 0LL;
		return fact[n] * factInv[n-r] % MOD * factInv[r] % MOD;
	};
    int N;
    while(cin >> N){
        long long res = 0;
        long long sum = 0;
        --N;
        for(int i=1;i<=N;i++){
            long long c = comb(i-1, N-i);
            long long cur = c * fact[i] % MOD * fact[N-i] % MOD;
            cur = (cur + MOD - sum) % MOD;
            sum = (sum + cur) % MOD;
            res = (res + i * cur) % MOD;
        }
        cout << res << endl;
    }
}