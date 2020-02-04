#include <iostream>
#include <cstdio>

using namespace std;

long long gcd(long long a, long long b){ return a%b ? gcd(b, a%b) : b; }

void solve(long long x, long long y){
    auto g = gcd(x, y);
    x /= g;
    y /= g;
    auto s = max(2LL, 2*x/y);
    bool find = false;
    for(long long i=s;i<s+2;i++){
        if(i%y) continue;
        long long nx = i*(i+1)/2 - x * (i/y);
        if(nx < 1 || i < nx) continue;
        cout << i << " " << nx << endl;
        find = true;
    }
    if(!find) cout << "Impossible" << endl;
}

int main(){
    long long x, y;
    while(~scanf("%lld/%lld", &x, &y)){
        solve(x, y);
    }
}