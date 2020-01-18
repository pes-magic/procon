#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    const int maxSize = 20000001;
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
    int H, W, K;
    while(cin >> H >> W >> K){
        long long res = K;
        for(int i=0;i<K;i++){
            long long add = 0;
            add += inv[H+W] * (W + H) % MOD;
            add += 2 * inv[H+W] * i % MOD * inv[H+W-1] % MOD * W % MOD * H % MOD;
            add = (add * (K-i)) % MOD;
            res = (res + add) % MOD;
        }
        res = res * perm(H+W, K) % MOD;
        cout << res << endl;
    }
}