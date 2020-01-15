#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    vector<long long> a(100001), b(100001), c(100001);
    a[0] = b[0] = c[0] = 1;
    for(int i=1;i<=100000;i++){
        auto a_b = (a[i-1] + b[i-1]) % MOD;
        auto ab = (a[i-1] * b[i-1]) % MOD;
        auto aa = (a[i-1] * a[i-1]) % MOD;
        auto a_b2 = (a_b * a_b) % MOD;
        auto a_b3 = (a_b2 * a_b) % MOD;
        a[i] = (a_b2 + (2 * ab + aa) * a[i-1]) % MOD;
        b[i] = ((2 * ab + aa) * b[i-1]) % MOD;
        c[i] = (3 * c[i-1] + a_b3) % MOD;
    }
    int L;
    while(cin >> L) cout << c[L] << endl;
}