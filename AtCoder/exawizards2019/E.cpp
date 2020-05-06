#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    const int maxSize = 200001;
	vector<long long> inv(maxSize);
    vector<long long> powinv2(maxSize);
	vector<long long> fact(maxSize);
	vector<long long> factInv(maxSize);
	for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
	for(int i=2;i<maxSize;i++){
		inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		fact[i] = fact[i-1] * i % MOD;
		factInv[i] = factInv[i-1] * inv[i] % MOD;
	}
    powinv2[0] = 1;
    for(int i=1;i<maxSize;i++) powinv2[i] = powinv2[i-1] * inv[2] % MOD;
	auto comb = [&](int n, int r){
		if(n < r || r < 0) return 0LL;
		return fact[n] * factInv[n-r] % MOD * factInv[r] % MOD;
	};
    int B, W; cin >> B >> W;
    long long allB = 0, allW = 0;
    cout << inv[2] << endl;
    for(int i=1;i<B+W;i++){
        allB = (allB + comb(i-1, B-1) * powinv2[i]) % MOD;
        allW = (allW + comb(i-1, W-1) * powinv2[i]) % MOD;
        cout << (allW + (1 + (MOD-allB) + (MOD-allW)) * inv[2])%MOD << endl;
    }
}