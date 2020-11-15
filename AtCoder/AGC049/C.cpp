#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N; cin >> N;
    vector<int> A(N), B(N);
    for(auto& t : A) cin >> t;
    for(auto& t : B) cin >> t;
    vector<int> des(N, 0);
    for(int i=0;i<N;i++){
        int src = A[i] - B[i];
        if(src <= 0) continue;
        int idxA = distance(A.begin(), lower_bound(A.begin(), A.end(), src));
        des[idxA]++;
        des[i]--;
    }
    for(int i=1;i<N;i++) des[i] += des[i-1];
    int rest = 0;
    for(int i=0;i<N;i++){
        if(!des[i] && A[i]-B[i] <= 0) ++rest;
    }
    int res = rest;
    for(int i=0;i<N;i++){
        if(A[i] > B[i]) continue;
        if(!des[i]) --rest;
        res = min(res, max(B[i]-A[i]+1, rest));
    }
    cout << res << endl;
}