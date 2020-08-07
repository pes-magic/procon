#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, W;
    while(cin >> N >> W){
        vector<int> v(N), w(N);
        for(int i=0;i<N;i++) cin >> v[i] >> w[i];
        vector<int> dp(W+1, 0);
        for(int i=0;i<N;i++){
            for(int j=0;j<=W-w[i];j++) dp[j+w[i]] = max(dp[j+w[i]], dp[j] + v[i]);
        }
        cout << dp.back() << endl;
    }
}