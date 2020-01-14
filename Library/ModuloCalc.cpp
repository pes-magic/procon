// 剰余計算
// verifyed
// 

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
// verifyed : https://atcoder.jp/contests/arc042/tasks/arc042_d
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

{
	vector<long long> inv(200002);
	vector<long long> fact(200002);
	vector<long long> factInv(200002);
	for(int i=0;i<2;i++) inv[i] = fact[i] = factInv[i] = 1;
	for(int i=2;i<=inv.size()-1;i++){
		inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		fact[i] = fact[i-1] * i % MOD;
		factInv[i] = factInv[i-1] * inv[i] % MOD;
	}
	auto comb = [&](int n, int r){
		if(n < r) return 0LL;
		return fact[n] * factInv[n-r] % MOD * factInv[r] % MOD;
	};
}