#include <iostream>

using namespace std;

long long modPow(long long a, long long p, long long mod){
    if(p == 0) return 1;
    auto res = modPow(a, p/2, mod);
    res = (res * res) % mod;
    if(p%2) res = (res * a) % mod;
    return res;
}

long long repMod(long long a, long long p, long long d, long long mod){
    if(p == 0) return 0;
    auto res = repMod(a, p/2, d, mod);
    res *= modPow(10, d*(p/2), mod) + 1;
    res %= mod;
    if(p%2){
        res = modPow(10, d, mod) * res + a;
        res %= mod;
    }
    return res;
}

long long calc(long long a, long long b, long long d, long long L, long long mod){
    if(L == 0) return 0;
    auto res = calc(a, b, d, L/2, mod);
    res *= modPow(10, d*(L/2), mod) + 1;
    res %= mod;
    res += repMod(L/2*b, L/2, d, mod);
    res %= mod;
    if(L%2){
        res = modPow(10, d, mod) * res + a + (L-1)*b;
        res %= mod;
    }
    return res;
}

int main(){
    long long L, A, B, M;
    while(cin >> L >> A >> B >> M){
        int d = 0; long long n10 = 1;
        while(n10 <= A){
            d++;
            n10 *= 10;
        }
        long long res = 0;
        while(L > 0){
            long long l = min(L, (n10 - A + B - 1) / B);
            res *= modPow(modPow(10, l, M), d, M);
            res %= M;
            res += calc(A, B, d, l, M);
            res %= M;
            A += B * l;
            L -= l;
            n10 *= 10;
            d++;
        }
        cout << res << endl;
    }
}