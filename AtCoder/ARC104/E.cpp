#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

const long long inv[7] = {1, 1, 500000004, 333333336, 250000002, 400000003, 166666668};

template<typename T>
int LIS(const vector<T>& v){
    if(v.empty()) return 0;
	vector<T> a(v.size(), v[0]);
    auto end = a.begin();
    ++end;
	for(int i=1;i<v.size();i++){
		auto l = lower_bound(a.begin(), end, v[i]);
        if(l == end) ++end;
        *l = v[i];
	}
	return distance(a.begin(), end);
}

long long comb(long long n, long long r){
    if(n < r) return 0;
    long long res = 1;
    for(int i=0;i<r;i++){
        res = res * (n-i) % MOD * inv[i+1] % MOD;
    }
    return res;
}

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

long long calcInv(long long a){
    return modPow(a, MOD-2);
}

long long count(const vector<int>& v){
    int check = 0;
    long long value = 0;
    vector<long long> dp(v.size()+1, 0);
    dp[0] = 1;
    while(check != v.size()){
        int next = check + 1;
        long long minValue = v[check];
        for(int i=check+1;i<v.size();i++){
            if(v[i] <= minValue){
                next = i+1;
                minValue = v[i];
            }
        }
        for(int i=v.size();i>=next;i--){
            for(int j=check;j<i;j++){
                dp[i] += dp[j] * comb(minValue - value, i-j) % MOD;
                dp[i] %= MOD;
            }
        }
        check = next;
        value = minValue;
    }
    return dp.back();
}

int solve(const vector<int>& A){
    const int N = A.size();
    if(N == 1) return 1;
    long long whole = 1;
    for(auto& t : A) whole = (whole * t) % MOD;
    long long res = 0;
    for(int i=0;i<(1<<(N-1));i++){
        vector<int> order(N, 0);
        for(int j=0;j<N-1;j++){
            order[j+1] = order[j] + ((i&(1<<j)) ? 1 : 0);
        }
        int m = order.back() + 1;
        do {
            vector<int> B(m, MOD);
            for(int j=0;j<N;j++){
                B[order[j]] = min(B[order[j]], A[j]);
            }
            res += count(B) * LIS(order) % MOD;
            res %= MOD;
        } while(next_permutation(order.begin(), order.end()));
    }
    return res * calcInv(whole) % MOD;
}

int main(){
    int N; cin >> N;
    vector<int> A(N);
    for(auto& t : A) cin >> t;
    cout << solve(A) << endl;
}