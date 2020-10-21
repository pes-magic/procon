#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main(){
    int N; cin >> N;
    vector<int> A(N), B(N);
    for(auto& t : A) cin >> t;
    for(auto& t : B) cin >> t;
    long long res = accumulate(A.begin(), A.end(), 0LL);
    vector<long long> odd, even;
    for(int i=0;i<N;i+=2){
        odd.emplace_back(B[i]-A[i]);
        even.emplace_back(B[i+1]-A[i+1]);
    }
    sort(odd.rbegin(), odd.rend());
    sort(even.rbegin(), even.rend());
    for(int i=0;i<N/2;i++){
        if(odd[i]+even[i] > 0) res += odd[i] + even[i];
    }
    cout << res << endl;
}