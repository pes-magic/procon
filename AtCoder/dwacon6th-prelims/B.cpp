#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
	vector<long long> inv(100000);
	vector<long long> fact(100000);
	for(int i=0;i<2;i++) inv[i] = fact[i] = 1;
	for(int i=2;i<inv.size();i++){
		inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		fact[i] = fact[i-1] * i % MOD;
	}
    int N;
    while(cin >> N){
        vector<int> x(N);
        for(auto& t : x) cin >> t;
        long long res = 0;
        long long c = 0;
        for(int i=1;i<N;i++){
            c += fact[N-1] * inv[i];
            c %= MOD;
            res += c * (x[i] - x[i-1]);
            res %= MOD;
        }
        cout << res << endl;
    }
}