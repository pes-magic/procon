#include <iostream>
#include <vector>

using namespace std;

int main(){
    int N, W;
    while(cin >> N >> W){
        vector<int> dp(100*N+1, W+1);
        dp[0] = 0;
        for(int i=0;i<N;i++){
            int v, w; cin >> v >> w;
            for(int j=dp.size()-1;j>=0;j--){
                if(j-v < 0) break;
                dp[j] = min(dp[j], dp[j-v]+w);
            }
        }
        int res = 0;
        for(int i=0;i<dp.size();i++) if(dp[i] <= W) res = i;
        cout << res << endl;
    }
}