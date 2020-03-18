#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    long long N, M, V, P;
    while(cin >> N >> M >> V >> P){
        vector<long long> A(N);
        for(auto& t : A) cin >> t;
        sort(A.begin(), A.end());
        int L = -1, R = N;
        while(R - L > 1){
            int mid = (L+R)/2;            
            if(N - mid <= P){
                R = mid;
                continue;
            }
            long long vote = M*V;
            bool ok = true;
            for(int i=N-1;i>=0;i--){
                if(i >= N-(P-1) || i == mid){
                    vote -= M;
                } else {
                    auto upper = A[mid] + M;
                    if(upper < A[i]) ok = false;
                    vote -= min(upper - A[i], M);
                }
            }
            if(ok && vote <= 0) R = mid;
            else L = mid;
        }
        cout << N-R << endl;
    }
}