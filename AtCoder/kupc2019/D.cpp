#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 998244353;

int main(){
    const int maxSize = 200001;
	vector<long long> inv(maxSize);
	vector<long long> fact(maxSize);
	vector<long long> factInv(maxSize);
	for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
	for(int i=2;i<maxSize;i++){
		inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		fact[i] = fact[i-1] * i % MOD;
		factInv[i] = factInv[i-1] * inv[i] % MOD;
	}
    auto catalan = [&](int n){
        if(n <= 0) return 1LL;
        return fact[2*n] * factInv[n] % MOD * factInv[n+1] % MOD;
    };
    int N; cin >> N;
    string S; cin >> S;
    char pre = '-';
    int cnt = 0;
    long long res = 1;
    for(auto& c : S){
        if(c != pre){
            res = (res * catalan(cnt)) % MOD;
            cnt = 1;
            pre = c;
        } else {
            ++cnt;
        }
    }
    res = (res * catalan(cnt)) % MOD;
    cout << res << endl;

}
