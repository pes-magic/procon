#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

int main(){
    int N; cin >> N;
    vector<long long> a(N);
    for(auto& t : a) cin >> t;
    long long sum = accumulate(a.begin(), a.end(), 0LL);
    long long best = sum;
    long long cur = 0;
    long long begin = 0, end = 0;
    while(end < N){
        if(cur < sum-cur){
            cur += a[end];
            ++end;
        } else {
            cur -= a[begin];
            ++begin;
        }
        best = min(best, abs(2*cur-sum));
    }
    cout << best << endl;
}