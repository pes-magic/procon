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

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N);
        for(auto& t : A) cin >> t;
        vector<int> p(1000001, 0);
        for(auto t : A){
            int val = t;
            for(int i=2;i*i<=val;i++){
                if(val%i) continue;
                int cnt = 0;
                while(val%i == 0){
                    val /= i;
                    ++cnt;
                }
                p[i] = max(p[i], cnt);
            }
            if(val > 1) p[val] = max(p[val], 1);
        }
        long long M = 1;
        for(int i=2;i<=1000000;i++) M = (M * modPow(i, p[i])) % MOD;
        long long res = 0;
        for(auto& t : A) res = (res + M * calcInv(t)) % MOD;
        cout << res << endl;
    }
}