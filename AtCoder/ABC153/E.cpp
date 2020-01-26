#include <iostream>
#include <vector>

using namespace std;

int main(){
    int H, N;
    while(cin >> H >> N){
        vector<int> A(N), B(N);
        for(int i=0;i<N;i++) cin >> A[i] >> B[i];
        vector<int> dp(H+1, 1000000007);
        dp[0] = 0;
        for(int i=0;i<H;i++){
            for(int j=0;j<N;j++){
                dp[min(H, i+A[j])] = min(dp[min(H, i+A[j])], dp[i] + B[j]);
            }
        }
        cout << dp.back() << endl;
    }
}