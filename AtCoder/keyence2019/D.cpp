#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

int solve(const vector<int>& A, const vector<int>& B){
    const int N = A.size(), M = B.size();
    if(A.back() != N*M || B.back() != N*M) return 0;
    int idxA = N-2, idxB = M-2;
    long long res = 1;
    for(int i=N*M-1;i>=1;i--){
        if(idxA >= 0 && idxB >= 0 && A[idxA] == i && B[idxB] == i){
            --idxA; --idxB;
        } else if(idxA >= 0 && A[idxA] == i){
            res = (res * (M-1-idxB)) % MOD;
            --idxA;
        } else if(idxB >= 0 && B[idxB] == i){
            res = (res * (N-1-idxA)) % MOD;
            --idxB;
        } else {
            int valid = max(0, (M-1-idxB) * (N-1-idxA) - (N*M - i));
            res = (res * valid) % MOD;
        }
    }
    return (int)res;
}

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<int> A(N), B(M);
        for(auto& t : A) cin >> t;
        for(auto& t : B) cin >> t;
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        cout << solve(A, B) << endl;
    }
}