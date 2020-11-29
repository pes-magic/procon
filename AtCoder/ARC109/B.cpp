#include <iostream>

using namespace std;

int main(){
    long long n; cin >> n;
    long long L = 0, R = (1LL << 31);
    while(R-L > 1){
        long long mid = (L+R)/2;
        if(mid*(mid+1)/2 <= n+1) L = mid;
        else R = mid;
    }
    cout << n-L+1 << endl;
}