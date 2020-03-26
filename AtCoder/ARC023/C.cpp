#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    const int maxSize = 2000;
	vector<long long> inv(maxSize);
	vector<long long> factInv(maxSize);
	for(int i=0;i<2;i++) inv[i] = factInv[i] = 1;
	for(int i=2;i<maxSize;i++){
		inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		factInv[i] = factInv[i-1] * inv[i] % MOD;
	}
    int N;
    while(cin >> N){
        vector<int> a(N);
        for(auto& t : a) cin >> t;
        int cur = a[0];
        int cnt = 0;
        long long res = 1;
        for(int i=1;i<N;i++){
            if(a[i] == -1){
                ++cnt;
            } else {
                long long dif = 1;
                for(long long j=0;j<cnt;j++) dif = (dif * (a[i]-cur+cnt-j)) % MOD;
                auto tmp = dif;
                dif = (dif * factInv[cnt]) % MOD;
                res = (res * dif) % MOD;
                cur = a[i];
                cnt = 0;
            }
        }
        cout << res << endl;
    }
}