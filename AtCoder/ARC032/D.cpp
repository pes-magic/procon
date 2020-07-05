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
    int N, K; cin >> N >> K;
    vector sum(3002, vector(3002, 0));
    for(int i=0;i<N;i++){
        int a, b; cin >> a >> b;
        ++sum[a+1][b+1];
    }
    for(int i=0;i<=3001;i++){
        for(int j=1;j<=3001;j++) sum[i][j] += sum[i][j-1];
    }
    for(int i=0;i<=3001;i++){
        for(int j=1;j<=3001;j++) sum[j][i] += sum[j-1][i];
    }
    auto getSum = [&](int x1, int y1, int x2, int y2){
        x2 = min(3001, x2);
        y2 = min(3001, y2);
        return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
    };
    int L = -1, R = 3000;
    long long res = comb(N, K);
    while(R-L > 1){
        int mid = (L+R)/2;
        long long cur = 0;
        for(int i=1;i<=3001;i++){
            for(int j=1;j<=3001;j++){
                int c = getSum(i, j, i, j);
                int b = getSum(i, j, i, j+mid) - c;
                int l = getSum(i, j, i+mid, j) - c;
                int a = getSum(i, j, i+mid, j+mid);
                if(a < K) continue;
                if(c == 0 && (b == 0 || l == 0)) continue;
                if(c > 0){
                    cur = (cur + comb(a, K)) % MOD;
                    cur = (cur + MOD - comb(a-c, K)) % MOD;
                }
                a -= c;
                if(a < K) continue;
                cur = (cur + comb(a, K) + comb(a-b-l, K)) % MOD;
                cur = (cur + 2*MOD - comb(a-b, K) - comb(a-l, K)) % MOD;
            }
        }
        if(cur == 0){
            L = mid;
        } else {
            R = mid;
            res = cur;
        }
    }
    cout << R << endl;
    cout << res << endl;
}