#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const int MOD = 998244353;
const int inv2 = (MOD - MOD/2) % MOD;

int main(){
    int N; cin >> N;
    vector<long long> cnt(1000001, 0);
    for(int i=0;i<N;i++){
        int a; cin >> a;
        cnt[a]++;
    }
    vector<long long> res(1000001, 0);
    for(int b=1000000;b>=1;b--){
        long long sum = 0;
        long long sumSq = 0;
        for(int t=1;t*b<=1000000;t++){
            long long d = t/b;
            sum = (sum + cnt[t*b] * t) % MOD;
            sumSq = (sumSq + cnt[t*b] * t % MOD * t) % MOD;
        }
        res[b] = (sum * sum % MOD + MOD - sumSq) % MOD * inv2 % MOD * b % MOD;
        for(int t=2;t*b<=1000000;t++){
            res[b] = (res[b] + MOD - t * res[t*b] % MOD) % MOD;
        }
    }
    cout << accumulate(res.begin(), res.end(), 0LL) % MOD << endl;
}