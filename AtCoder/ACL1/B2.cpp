#include <iostream>
#include <numeric>
#include <atcoder/math>

using namespace std;

int main(){
    long long N; cin >> N;
    N *= 2;
    long long res = N;
    vector<long long> r(2), m(2);
    for(long long i=1;i*i<N;i++){
        if(N%i) continue;
        long long d = N/i;
        if(std::gcd(i, d) != 1) continue;
        r[0] = 0, r[1] = d-1;
        m[0] = i, m[1] = d;
        auto v = atcoder::crt(r, m);
        res = min(res, v.first ? v.first : v.second);
        swap(m[0], m[1]);
        r[1] = i-1;
        v = atcoder::crt(r, m);
        res = min(res, v.first ? v.first : v.second);
    }
    cout << res << endl;
}