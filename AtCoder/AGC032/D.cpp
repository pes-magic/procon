#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N;
    long long A, B;
    while(cin >> N >> A >> B){
        vector<int> p(N);
        for(auto& t : p) cin >> t;
        vector<long long> dp(2*N+1, 0);
        bool find1 = false;
        for(int i=0;i<=2*N;i++){
            if(i%2 == 1 && p[i/2] == 1){
                find1 = true;
            } else {
                dp[i] = (find1 ? A : B);
            }
        }
        for(int i=2;i<=N;i++){
            vector<long long> next(2*N+1, 0);
            long long m = dp[0];
            bool find = false;
            for(int j=0;j<=2*N;j++){
                if(j%2 == 1){
                    if(p[j/2] == i){
                        next[j] = m;
                        find = true;
                    } else {
                        next[j] = m + (find ? A : B);
                    }
                } else {
                    next[j] = min(m, dp[j]) + (find ? A : B);
                }
                m = min(m, dp[j]);
            }
            dp = next;
        }
        cout << *min_element(dp.begin(), dp.end()) << endl;
    }
}