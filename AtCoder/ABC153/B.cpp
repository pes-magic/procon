#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main(){
    long long H, N;
    while(cin >> H >> N){
        vector<long long> A(N);
        for(auto& t : A) cin >> t;
        cout << (H <= accumulate(A.begin(), A.end(), 0LL) ? "Yes" : "No") << endl;
    }
}