#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

int main(){
	vector<long long> inv(100001);
	vector<long long> fact(100001);
	vector<long long> factInv(100001);
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
        vector<long long> A(N);
        for(auto& t : A) cin >> t;
        sort(A.begin(), A.end());
        auto whole = comb(N, K);
        long long res = 0;
        for(int i=0;i+1<N;i++){
            int n1 = i+1;
            int n2 = N-n1;
            auto c = whole+2*MOD-comb(n1, K)-comb(n2, K);
            res += c * (A[i+1] - A[i]);
            res %= MOD;
        }
        cout << res << endl;
    }
}