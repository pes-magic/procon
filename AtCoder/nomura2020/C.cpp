#include <iostream>
#include <vector>

using namespace std;

long long solve(const vector<int>& A){
    long long res = 1;
    long long rest = 1 - A[0];
    if(rest < 0) return -1;
    vector<long long> req(A.size(), 0);
    req.back() = A.back();
    for(int i=A.size()-2;i>=0;i--) req[i] = req[i+1] + A[i];
    for(int i=1;i<A.size();i++){
        rest = min(req[i], 2*rest);
        if(rest < A[i]) return -1;
        res += rest;
        rest -= A[i];
    }
    return res;
}

int main(){
    int N; cin >> N;
    vector<int> A(N+1);
    for(auto& a : A) cin >> a;
    cout << solve(A) << endl;
}