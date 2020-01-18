#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

int main(){
    int N;
    while(cin >> N){
        vector<long long> A(N);
        long long sum = 0;
        for(auto& t : A) cin >> t;
        sum = accumulate(A.begin(), A.end(), 0LL);
        long long res = (1LL << 60);
        long long s = 0;
        for(int i=0;i<N-1;i++){
            s += A[i];
            res = min(res, abs(sum-2*s));
        }
        cout << res << endl;
    }
}