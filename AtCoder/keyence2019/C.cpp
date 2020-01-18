#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve(const vector<int>& A, const vector<int>& B){
    vector<int> spare;
    long long lack = 0;
    long long res = 0;
    for(int i=0;i<A.size();i++){
        if(A[i] < B[i]){ lack += B[i] - A[i]; res++; }
        else { spare.emplace_back(A[i]-B[i]); }
    }
    if(lack == 0) return res;
    sort(spare.rbegin(), spare.rend());
    for(auto& s : spare){
        lack -= s;
        ++res;
        if(lack <= 0) return res;
    }
    return -1;
}

int main(){
    int N;
    while(cin >> N){
        vector<int> A(N), B(N);
        for(auto& t : A) cin >> t;
        for(auto& t : B) cin >> t;
        cout << solve(A, B) << endl;
    }
}