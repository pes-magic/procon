#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

const int MOD = 998244353;

int main(){
    int N; cin >> N;
    vector<long long> a(N);
    for(auto& t : a) cin >> t;
    sort(a.begin(), a.end());
    long long res = a[0];
    for(int i=1;i<N;i++){
        res = (res * gcd(i, a[i])) % MOD;
    }
    cout << res << endl;
}