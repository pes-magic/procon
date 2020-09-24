#include <iostream>
#include <numeric>

using namespace std;

long long extgcd(long long a, long long b, long long &x, long long &y) {
    long long g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}

int main(){
    long long N; cin >> N;
    N *= 2;
    long long res = N;
    for(long long i=1;i*i<N;i++){
        if(N%i) continue;
        long long d = N/i;
        if(std::gcd(i, d) != 1) continue;
        long long x, y;
        extgcd(i, d, x, y);
        for(int k=-1;k<=1;k++){
            auto nx = x + k * d;
            auto ny = y - k * i;
            if(nx == 0 || ny == 0) continue;
            if(nx > 0) res = min(res, nx*i-1);
            else res = min(res, ny*d-1);
        }
    }
    cout << res << endl;
}