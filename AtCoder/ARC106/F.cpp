#include <iostream>

using namespace std;

const int MOD = 998244353;

int main(){
    int N; cin >> N;
    long long res = 1;
    long long sum = 0;
    for(int i=0;i<N;i++){
        int d; cin >> d;
        sum = (sum + d) % MOD;
        res = (res * d) % MOD;
    }
    for(int i=0;i<N-2;i++){
        res = res * (sum + MOD - N - i) % MOD;
    }
    cout << res << endl;
}