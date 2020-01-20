#include <iostream>
#include <vector>

using namespace std;

long long modPow(long long a, long long p, int MOD){
    if(p == 0) return 1;
    auto res = modPow(a, p/2, MOD);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

long long modSeqOneCalc(long long p10, long long p, int MOD){
    if(p == 1) return 1;
    long long res = modSeqOneCalc(p10, p/2, MOD);
    res = (modPow(p10, p/2, MOD) + 1) * res % MOD;
    if(p%2) res = (p10 * res + 1) % MOD;
    return res;
}

long long modSeqOne(long long d, long long p, int MOD){
    return modSeqOneCalc(modPow(10, d, MOD), p, MOD);
}

long long gcd(long long a, long long b){ return a%b ? gcd(b, a%b) : b; }

int main(){
    long long A, B, M;
    while(cin >> A >> B >> M){
        auto g = gcd(A, B);
        cout << modSeqOne(1, A, M) * modSeqOne(g, B/g, M) % M << endl;
    }
}
