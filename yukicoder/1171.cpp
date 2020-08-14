#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1000000007;

long long solve(const string& S){
    const int N = S.size();
    const int maxSize = N+1;
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
    vector<vector<int>> pos(26);
    vector<long long> pow(N+1, 1);
    for(int i=1;i<=N;i++) pow[i] = 2*pow[i-1]%MOD;
    long long res = 0;
    for(int i=1;i<=N;i++) res = (res + i * comb(N, i)) % MOD;
    for(int i=0;i<N;i++) pos[S[i]-'a'].push_back(i);
    for(auto& v : pos){
        if(v.size() < 2) continue;
        long long base = pow[v[0]];
        for(int i=1;i<v.size();i++){
            long long sub = (base * pow[N-v[i]-1]) % MOD;
            res = (res + MOD - sub) % MOD;
            base = (base + pow[v[i]]) % MOD;
        }
    }
    return res;
}

int main(){
    string S;
    while(cin >> S){
        cout << solve(S) << endl;
    }
}