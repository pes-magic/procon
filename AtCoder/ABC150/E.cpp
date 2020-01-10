#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

int main(){
    int N;
    while(cin >> N){
        vector<long long> C(N);
        for(auto& t : C) cin >> t;
        sort(C.begin(), C.end());
        long long d2 = 1;
        for(int i=0;i<2*(N-1);i++) d2 = (2*d2)%MOD;
        long long d3 = (2*d2)%MOD;
        long long sum = 0;
        for(int i=0;i<N;i++){
            sum += (d2 * (N-1-i) + d3) % MOD * C[i];
            sum %= MOD;
        }
        cout << sum << endl;
    }
}