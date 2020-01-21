#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main(){
    const int maxSize = 1000001;
	vector<long long> inv(maxSize);
	for(int i=0;i<2;i++) inv[i] = 1;
	for(int i=2;i<maxSize;i++){
		inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
	}
    vector<int> primes; primes.push_back(2);
    for(int i=3;i<1000;i+=2){
        bool ok = true;
        for(auto& p : primes) if(i%p == 0) ok = false;
        if(ok) primes.push_back(i);
    }
    int N;
    while(cin >> N){
        vector<long long> sum(1000001, 0), sqsum(1000001, 0);
        for(int i=0;i<N;i++){
            long long A; cin >> A;
            vector<vector<int>> divs;
            int a = (int)A;
            for(int j=0;j<primes.size() && primes[j]*primes[j]<=a;j++){
                if(a%primes[j]) continue;
                divs.emplace_back(vector<int>(1, 1));
                while(a%primes[j] == 0){
                    divs.back().push_back(divs.back().back() * primes[j]);
                    a /= primes[j];
                }
            }
            if(a > 1){ divs.push_back(vector<int>({1, a})); }
            if(A == 1) divs.push_back(vector<int>(1, 1));
            int m = 1;
            for(auto& v : divs) m *= v.size();
            for(int j=0;j<m;j++){
                int idx = j;
                int val = 1;
                for(auto& v : divs){
                    val *= v[idx%v.size()];
                    idx /= v.size();
                }
                sum[val] = (sum[val] + A) % MOD;
                sqsum[val] = (sqsum[val] + A * A) % MOD;
            }
        }
        long long res = 0;
        vector<long long> val(1000001, 0);
        for(int i=1000000;i>=1;i--){
            val[i] = (sum[i] * sum[i] - sqsum[i]) % MOD * inv[2] % MOD;
            for(int j=2*i;j<=1000000;j+=i) val[i] = (val[i] + MOD - val[j]) % MOD;
            res = (res + val[i] * inv[i]) % MOD;
        }
        cout << res << endl;
    }
}