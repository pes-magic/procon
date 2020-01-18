#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    const int maxSize = 100001;
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
    int R, C;
    while(cin >> R >> C){
        int X, Y, D, L; cin >> X >> Y >> D >> L;
        vector<vector<long long>> dp(X+1, vector<long long>(Y+1, 0));
        for(int i=1;i<=X;i++){
            for(int j=1;j<=Y;j++){
                if(i*j < D+L) continue;
                dp[i][j] = fact[i*j] * factInv[D] % MOD * factInv[L] % MOD * factInv[i*j-D-L] % MOD;
                for(int ii=1;ii<=i;ii++){
                    for(int jj=1;jj<=j;jj++){
                        int m = (i-ii+1) * (j-jj+1);
                        if(m == 1) continue;
                        dp[i][j] = (dp[i][j] + MOD - dp[ii][jj] * m % MOD) % MOD;
                    }
                }
            }
        }
        long long mul = (R-X+1) * (C-Y+1);
        cout << (mul * dp[X][Y] % MOD) << endl;
    }
}