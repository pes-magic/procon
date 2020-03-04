#include <iostream>

using namespace std;

int main(){
    long long N, K;
    while(cin >> N >> K){
        long long res = 0;
        for(int b=K+1;b<=N;b++){
            if(K==0){
                res += N;
            } else {
                long long blk = N/b;
                res += blk * (b-K);
                res += max(0LL, N - blk*b - K + 1);
            }
        }
        cout << res << endl;
    }
}