#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int MOD = 1000000007;

int divNum(int t){
    int res = 1;
    for(int d=2;d*d<=t;d++){
        if(t%d) continue;
        int cnt = 0;
        while(t%d == 0){
            ++cnt;
            t /= d;
        }
        res *= cnt + 1;
    }
    if(t > 1) res *= 2;
    return res;
}

vector<int> getDivs(int t){
    vector<int> res;
    for(int i=1;i*i<=t;i++){
        if(t%i) continue;
        res.push_back(i);
        if(i*i != t) res.push_back(t/i);
    }
    sort(res.begin(), res.end());
    return res;
}

int solve(int N, int M){
    if(N == 1) return 1;
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
    int d = divNum(N);
    auto divs = getDivs(N);
    map<int, int> key;
    for(int i=0;i<divs.size();i++) key[divs[i]] = i;
    vector<vector<long long>> dp(divs.size(), vector<long long>(min<int>(M, d)+1, 0));
    for(int i=0;i<dp[0].size();i++){
        dp.back()[i] = comb(M, i);
    }
    for(int i=1;i<divs.size();i++){
        for(int j=i;j<dp.size();j++){
            int val = divs[j];
            for(int l=1;;l++){
                if(val%divs[i]) break;
                val /= divs[i];
                int idx = key[val];
                for(int k=l;k<dp[j].size();k++){
                    dp[idx][k-l] += dp[j][k] * comb(k, l);
                    dp[idx][k-l] %= MOD;
                }
            }
        }
    }
    return dp[0][0];
}

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
	};    int N, M;
    while(cin >> N >> M){
        int sgn = (N > 0 ? 1 : -1);
        auto res = solve(abs(N), M);
        long long minus = 0;
        for(int i=(N > 0 ? 0 : 1);i<=M;i+=2){
            minus += comb(M, i);
            minus %= MOD;
        }
        cout << (res * minus) % MOD << endl;
    }
}