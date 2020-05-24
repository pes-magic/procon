#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    long long N, M, V, P; cin >> N >> M >> V >> P;
    vector<long long> A(N);
    for(auto& t : A) cin >> t;
    sort(A.begin(), A.end());
    int L = -1, R = N-1;
    while(R-L > 1){
        int mid = (L+R)/2;
        long long thr = A[mid] + M;
        int gr = 0;
        long long add = M;
        for(int j=N-1;j>=0;j--){
            if(j == mid) continue;
            if(A[j] > thr){
                gr++;
                add += M;
            } else {
                if(gr+1 < P && A[j]+M > thr){
                    gr++;
                    add += M;
                } else {
                    add += min(M, thr-A[j]);
                }
            }
        }
        if(gr < P && add >= M*V) R = mid;
        else L = mid;
    }
    cout << N-R << endl;
}