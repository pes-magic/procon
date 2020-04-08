#include <iostream>
#include <vector>

using namespace std;

long long f(long long b, long long n){
    long long res = 0;
    while(n){
        res += n%b;
        n /= b;
    }
    return res;
}

long long solve(long long n, long long s){
    for(long long b=2;b*b<=n;b++){
        if(f(b, n) == s) return b;
    }
    long long res = -1;
    for(long long d=1;d*d<n;d++){
        auto src = n/(d+1) + 1;
        auto dst = n/d;
        if(n-s+d < 0) continue;
        if((n-s+d)%d != 0) continue;
        auto c = (n-s+d)/d;
        if(c < src || dst < c) continue;
        if(res == -1 || c < res) res = c;
    }
    if(res != -1) return res;
    if(s == n) return n+1;
    return -1;
}

int main(){
    long long n, s;
    while(cin >> n >> s){
        cout << solve(n, s) << endl;
    }
}