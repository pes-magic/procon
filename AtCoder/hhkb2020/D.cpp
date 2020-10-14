#include <iostream>

using namespace std;

const int MOD = 1000000007;

long long solve(long long N, long long A, long long B){
    if(A < B) swap(A, B);
    long long sub = (N-A+1) * (A-B+1) % MOD;
    if(A < N && B >= 2){
        long long src = (N-A);
        long long dst = max(1LL, N-(A+B-1)+1);
        sub += (src+dst)*(src-dst+1) % MOD;
        sub %= MOD;
    }
    sub = (sub * sub) % MOD;
    long long whole = (N-A+1) * (N-A+1) % MOD * (N-B+1) % MOD * (N-B+1) % MOD;
    return (whole + MOD - sub) % MOD;
}

int main(){
    int T; cin >> T;
    for(int i=0;i<T;i++){
        long long N, A, B; cin >> N >> A >> B;
        cout << solve(N, A, B) << endl;
    }
}