#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n, m;
    while(cin >> n >> m){
        vector<int> d(m);
        for(auto& t : d) cin >> t;
        vector<int> dp(n+1, n);
        dp[0] = 0;
        for(int i=0;i<n;i++){
            for(auto& t : d){
                if(i+t > n) continue;
                dp[i+t] = min(dp[i+t], dp[i]+1);
            }
        }
        cout << dp.back() << endl;
    }
}