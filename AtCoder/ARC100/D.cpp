#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N; cin >> N;
    vector<long long> A(N+1, 0);
    for(int i=1;i<=N;i++){
        cin >> A[i];
        A[i] += A[i-1];
    }
    auto div = [&](int src, int end){
        auto whole = A[end] - A[src];
        int L = src, R = end;
        while(R-L > 1){
            int mid = (L+R)/2;
            auto s = A[mid] - A[src];
            if(s < whole-s) L = mid;
            else R = mid;
        }
        return L;
    };
    long long res = A.back();
    for(int i=2;i<=N-2;i++){
        int d1 = div(0, i);
        int d2 = div(i, N);
        for(int j=0;j<2;j++){
            if(d1+j == 0 || d1+j == i) continue;
            for(int k=0;k<2;k++){
                if(d2+k == i || d2+k == N) continue;
                long long m = A[d1+j] - A[0];
                long long M = m;
                m = min(m, A[i] - A[d1+j]);
                M = max(M, A[i] - A[d1+j]);
                m = min(m, A[d2+k] - A[i]);
                M = max(M, A[d2+k] - A[i]);
                m = min(m, A[N] - A[d2+k]);
                M = max(M, A[N] - A[d2+k]);
                res = min(res, M-m);
            }
        }
    }
    cout << res << endl;
}