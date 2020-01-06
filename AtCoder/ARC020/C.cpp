#include <iostream>
#include <vector>

using namespace std;

long long modPow(long long a, long long p, long long mod){
    if(p == 0) return 1;
    auto res = modPow(a, p/2, mod);
    res = (res * res) % mod;
    if(p%2) res = (res * a) % mod;
    return res;
}

long long modSeq(long long a, long long l, long long v10, long long mod){
    if(l == 1) return a%mod;
    auto res = modSeq(a, l/2, v10, mod);
    res = (res * (modPow(v10, l/2, mod) + 1)) % mod;
    if(l%2) res = (res * v10 + a) % mod;
    return res;
}

int len(int m){
    int res = 0;
    while(m) ++res, m /= 10;
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N), L(N);
        for(int i=0;i<N;i++) cin >> A[i] >> L[i];
        int B; cin >> B;
        long long res = 0;
        for(int i=0;i<N;i++){
            int l = len(A[i]);
            long long v10 = 1;
            for(int j=0;j<l;j++) v10 = (10 * v10) % B;
            res *= modPow(v10, L[i], B);
            res += modSeq(A[i], L[i], v10, B);
            res %= B;
        }
        cout << res << endl;
    }
}