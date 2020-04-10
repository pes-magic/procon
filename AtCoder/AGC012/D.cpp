#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

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
    int N, X, Y;
    while(cin >> N >> X >> Y){
        vector<vector<int>> w(N);
        int low1 = MOD, low2 = MOD, lowIdx = -1;
        for(int i=0;i<N;i++){
            int a, b; cin >> a >> b;
            w[a-1].push_back(b);
            if(b < low1){
                low2 = low1; low1 = b; lowIdx = a-1;
            } else if(b < low2){
                low2 = b;
            }
        }
        long long res = 1;
        int cnt = 0;
        for(int i=0;i<N;i++){
            if(w[i].empty()) continue;
            int m = *min_element(w[i].begin(), w[i].end());
            int lowest = (i == lowIdx ? low2 : low1);
            if(lowest + m > Y) continue;
            int l = count_if(w[i].begin(), w[i].end(), [&](int t){ return m+t <= X || lowest+t <= Y; });
            res = (res * factInv[l]) % MOD;
            cnt += l;
        }
        res = (res * fact[cnt]) % MOD;
        cout << res << endl;
    }
}