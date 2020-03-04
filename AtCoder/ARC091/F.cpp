#include <iostream>

using namespace std;

int grundy(int A, int K){
    if(A < K) return 0;
    if(A%K == 0) return A/K;
    int blk = A/K;
    int src = blk * (K-1);
    return grundy(src + (A-src)%(blk+1), K);
}

int main(){
    int N;
    while(cin >> N){
        int g = 0;
        for(int i=0;i<N;i++){
            int A, K; cin >> A >> K;
            g ^= grundy(A, K);
        }
        cout << (g ? "Takahashi" : "Aoki") << endl;
    }
}