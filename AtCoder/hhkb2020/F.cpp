#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

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

int main(){
    const int maxSize = 1002;
    vector<long long> inv(maxSize);
    for(int i=0;i<2;i++) inv[i] = 1;
    for(int i=2;i<maxSize;i++){
        inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
    }
    int N; cin >> N;
    vector<pair<long long, long long>> vp(N);
    long long lowest = 0;
    for(auto& p : vp){
         cin >> p.first >> p.second;
         lowest = max(lowest, p.first);
    }
    vector<long long> rangeInv(N);
    for(int i=0;i<N;i++) rangeInv[i] = calcInv(vp[i].second - vp[i].first);
    vector<long long> v;
    for(auto& p : vp){
        if(lowest <= p.first) v.push_back(p.first);
        if(lowest <= p.second) v.push_back(p.second);
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    long long res = 0;
    long long prob = 0;
    for(int i=0;i+1<v.size();i++){
        vector<long long> dp(N+1, 0);
        dp[0] = 1;
        int size = 1;
        for(int j=0;j<N;j++){
            long long keep = (min(v[i], vp[j].second) - vp[j].first) * rangeInv[j] % MOD;
            long long up = max(0LL, min(v[i+1], vp[j].second) - max(v[i], vp[j].first)) * rangeInv[j] % MOD;
            for(int k=size-1;k>=0;k--){
                dp[k+1] = (dp[k+1] + dp[k] * up) % MOD;
                dp[k] = (dp[k] * keep) % MOD;
            }
            if(up) ++size;
        }
        for(int j=1;j<size;j++){
            prob = (prob + dp[j]) % MOD;
            res += (j * inv[j+1] % MOD * (v[i+1] - v[i]) % MOD + v[i]) % MOD * dp[j] % MOD;
        }
    }
    for(int i=0;i<N;i++){
        res = (res * (i+2)) % MOD;
        res = (res * (vp[i].second - vp[i].first)) % MOD;
    }
    cout << res << endl;
}
