#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MOD = 1000003;

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
    vector<long long> t(MOD);
    t[0] = 0;
    t[1] = 1;
    for(int i=2;i<MOD;i++) t[i] = t[i-1] * i % MOD;
    int Q; cin >> Q;
    for(int _=0;_<Q;_++){
        int x, d, n; cin >> x >> d >> n;
        if(x == 0 || d == 0){
            cout << modPow(x, n) << endl;
        } else {
            auto inv_d = calcInv(d);
            auto start = x * inv_d % MOD;
            if(start + n - 1 >= MOD){
                cout << 0 << endl;
                continue;
            }
            cout << t[start+n-1] * calcInv(t[start-1]) % MOD * modPow(d, n) % MOD << endl;
        }
    }
}