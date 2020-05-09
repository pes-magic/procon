#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    const int maxSize = 100001;
	vector<long long> inv(maxSize);
	vector<long long> invSum(maxSize);
    vector<long long> fact(maxSize);
	vector<long long> factInv(maxSize);
	for(int i=0;i<2;i++) inv[i] = fact[i] = invSum[i] = 1;
	for(int i=2;i<maxSize;i++){
		inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
        fact[i] = fact[i-1] * i % MOD;
        invSum[i] = (invSum[i-1] + inv[i]) % MOD;
	}
    int N; cin >> N;
    vector<long long> A(N);
    for(auto& t : A) cin >> t;
    long long res = 0;
    for(int i=0;i<N;i++){
        res = (res + A[i] * (invSum[N-i] + invSum[i+1] + MOD - 1)) % MOD;
    }
    res = (res * fact[N]) % MOD;
    cout << res << endl;
}