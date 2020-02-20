#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, K;
    while(cin >> N >> K){
        vector<int> A(N), B(N);
        for(int i=0;i<N;i++) cin >> A[i] >> B[i];
        long long res = 0;
        for(int i=0;i<N;i++){
            if((K|A[i]) == K) res += B[i];
        }
        for(int i=0;i<30;i++){
            if(!(K&(1<<i))) continue;
            long long cur = 0;
            int mask = ~((1<<i)-1);
            for(int j=0;j<N;j++){
                if(A[j]&(1<<i)) continue;
                if(((K|A[j])&mask) == (K&mask)) cur += B[j];
            }
            res = max(res, cur);
        }
        cout << res << endl;
    }
}