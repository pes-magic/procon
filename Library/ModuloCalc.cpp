// 剰余計算
// verified
// https://atcoder.jp/contests/keyence2019/tasks/keyence2019_f

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

// 離散対数 (a^x = target (mod MOD) なる x を求める)
// verified : https://atcoder.jp/contests/arc042/tasks/arc042_d
int moduloLog(int a, int target){
    int sq = sqrt(MOD);
    long long m = 1;
    map<int, int> mp;
    for(int i=0;i<sq;i++){
        if(!mp.count(m)) mp[m] = i;
        m = (m * X) % P;
    }
    auto inv = modPow(modPow(X, sq), MOD-2);
    for(int i=0;i<=sq;i++){
        if(mp.count(target)){
            return i * sq + mp[target];
        }
        target = (target * inv) % MOD;
    }
    return -1;
}

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
    auto catalan = [&](int n){
        if(n <= 0) return 1LL;
        return fact[2*n] * factInv[n] % MOD * factInv[n+1] % MOD;
    };
