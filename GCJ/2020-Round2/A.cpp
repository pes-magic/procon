#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

long long calc(long long rest, long long start){
    long long low = 0, high = 2000000000;
    while(high - low > 1){
        long long mid = (low+high)/2;
        long long n = mid*(start+mid-1);
        if(n <= rest) low = mid;
        else high = mid;
    }
    return low;
}

void solve(long long L, long long R){
    bool swp = (L < R);
    if(swp) swap(L, R);
    long long dif = L - R;
    long long low = 0, high = 2000000000;
    while(high - low > 1){
        long long mid = (low+high)/2;
        long long n = mid*(mid+1)/2;
        if(n <= dif) low = mid;
        else high = mid;
    }
    L -= low*(low+1)/2;
    if(L == R) swp = false;
    long long res = low;
    long long l = calc(L, low+1);
    long long r = calc(R, low+2);
    if(l <= r) r = l;
    else l = min(l, r+1);
    res += l+r;
    L -= l*(low+1+l-1);
    R -= r*(low+2+r-1);
    if(swp) swap(L, R);
    cout << res << " " << L << " " << R << endl;
}

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        long long L, R; cin >> L >> R;
        printf("Case #%d: ", t);
        solve(L, R);
    }
}