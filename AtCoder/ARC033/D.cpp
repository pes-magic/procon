#include <iostream>
#include <vector>

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

int solve(const vector<long long>& A, long long T){
    const int N = A.size() - 1;
    if(T <= N) return A[T];
    long long curL = 1;
    for(int i=1;i<=N;i++) curL = (curL * (MOD - i)) % MOD;
    vector<long long> P(N+1);
    for(int i=0;i<=N;i++){
        P[i] = (A[i] * calcInv(curL)) % MOD;
        curL = (curL * (i+1)) % MOD;
        curL = (curL * calcInv(MOD - (N-i))) % MOD;
    }
    long long prod = 1;
    for(int i=0;i<=N;i++) prod = (prod * (T - i)) % MOD;
    long long res = 0;
    for(int i=0;i<=N;i++){
        long long p = (prod * calcInv(T - i)) % MOD;
        res = (res + P[i] * p) % MOD;
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<long long> A(N+1);
        for(auto& a : A) cin >> a;
        long long T; cin >> T;
        cout << solve(A, T) << endl;
    }
}