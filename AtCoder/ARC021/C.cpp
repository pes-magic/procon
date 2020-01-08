#include <iostream>
#include <vector>

using namespace std;

int main(){
    int K, N;
    while(cin >> K >> N){
        vector<long long> A(N), D(N);
        for(int i=0;i<N;i++) cin >> A[i] >> D[i];
        long long L = 0, R = 1LL << 40;
        while(R - L > 1){
            long long cnt = 0;
            long long mid = (L+R)/2;
            for(int i=0;i<N;i++){
                if(mid < A[i]) continue;
                cnt += (mid - A[i])/D[i] + 1;
            }
            if(cnt >= K) R = mid;
            else L = mid;
        }
        long long res = 0;
        for(int i=0;i<N;i++){
            if(R - 1 < A[i]) continue;
            long long m = (R - 1 - A[i])/D[i] + 1;
            res += A[i] * m + (m - 1) * m / 2 * D[i];
            K -= m;
        }
        res += K * R;
        cout << res << endl;
    }
}