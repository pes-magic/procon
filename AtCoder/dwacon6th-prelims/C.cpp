#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
	vector<long long> inv(1001);
	vector<long long> fact(1001);
	vector<long long> factInv(1001);
	for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
	for(int i=2;i<inv.size();i++){
		inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		fact[i] = fact[i-1] * i % MOD;
		factInv[i] = factInv[i-1] * inv[i] % MOD;
	}
	auto comb = [&](int n, int r){
		if(n < r || r < 0) return 0LL;
		return fact[n] * factInv[n-r] % MOD * factInv[r] % MOD;
	};
    int N, K;
    while(cin >> N >> K){
        vector<int> a(K);
        for(auto& t : a) cin >> t;
        vector<long long > dp(N+1, 0);
        dp[0] = fact[N];
        for(auto t : a){
            vector<long long> next(N+1, 0);
            for(int i=0;i<=N;i++){
                for(int j=0;j+i<=N;j++){
                    next[i+j] += dp[i] * comb(N-j, t-j) % MOD * factInv[j];
                    next[i+j] %= MOD;
                }
            }
            dp = next;
        }
        cout << dp.back() << endl;
    }
}