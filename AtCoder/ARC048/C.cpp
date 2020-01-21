#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

long long gcd(long long a, long long b){ return a%b ? gcd(b, a%b) : b; }

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<long long> L(N);
        for(auto& t : L) cin >> t;
        auto m = *min_element(L.begin(), L.end());
        long long g = 0;
        for(auto& t : L){
            if(t == m) continue;
            g = (g == 0 ? t-m : gcd(g, t-m));
        }
        cout << modPow(2, m + (g+1)/2) << endl;
    }
}