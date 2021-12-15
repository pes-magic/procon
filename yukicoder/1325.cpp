#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int main(){
    int N; cin >> N;
    long long res = 0;
    for(int i=0;i<N;i++){
        long long a; cin >> a;
        res += a * (i+2) % MOD;
        res %= MOD;
    }
    if(N==1) res = (MOD - MOD / 2)*res%MOD;
    for(int i=0;i<N-2;i++) res = 2*res%MOD;
    cout << res << endl;
}