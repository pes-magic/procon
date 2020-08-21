#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int f(int t){
    if(t < 10) return 1;
    if(t < 100) return 2;
    if(t < 1000) return 3;
    if(t < 10000) return 4;
    if(t < 100000) return 5;
    if(t < 1000000) return 6;
    if(t < 10000000) return 7;
    if(t < 100000000) return 8;
    return 9;
}

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

int solve(int S){
    int high = 1;
    int sum = 0;
    int res = 0;
    for(int i=1;i<10000000;i++){
        while(sum < S){
            sum += f(high);
            ++high;
        }
        if(sum == S) ++res;
        sum -= f(i);
    }
    for(int d=1;;d++){
        int m = S/d;
        if(m < 8) break;
        if(S%d == 0){
            long long add = (9 * modPow(10, m-1) % MOD + MOD - d + 1) % MOD;
            res = (res + add) % MOD;
        } else {
            ++res;
        }
    }
    return res%MOD;
}

int main(){
    int S; cin >> S;
    cout << solve(S) << endl;
}