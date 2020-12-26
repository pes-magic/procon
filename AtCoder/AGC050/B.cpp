#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1000000000;

int main(){
    int N; cin >> N;
    vector ok(N+1, vector(N+1, -INF));
    vector ng(N+1, vector(N+1, -INF));
    vector<int> a(N);
    for(auto& t : a) cin >> t;
    vector<int> sumA(N+1, 0);
    for(int i=0;i<N;i++) sumA[i+1] = sumA[i] + a[i];
    for(int i=0;i<=N;i++) ok[i][i] = ng[i][i] = 0;
    vector<int> bestOK(N+1, -INF);
    vector<int> bestNG(N+1, -INF);
    int res = 0;
    for(int d=3;d<=N;d+=3){
        for(int i=0;i+d<=N;i++){
            ok[i][i+d] = sumA[i+d] - sumA[i];
            ng[i][i+d] = -ok[i][i+d];
            fill(bestOK.begin(), bestOK.end(), -INF);
            fill(bestNG.begin(), bestNG.end(), -INF);
            bestOK[i] = 0;
            bestNG[i] = 0;
            for(int j=i;j<i+d;j++){
                for(int k=0;j+1+k<=i+d;k+=3){
                    bestOK[j+1+k] = max(bestOK[j+k+1], bestOK[j] + ng[j+1][j+1+k]);
                    bestNG[j+1+k] = max(bestNG[j+k+1], bestNG[j] + ok[j+1][j+1+k]);
                }
            }
            ok[i][i+d] += max(0, bestOK[i+d]);
            ng[i][i+d] += max(0, bestNG[i+d]);
        }
    }
    vector<int> dp(N+1, -INF);
    dp[0] = 0;
    for(int i=0;i<N;i++){
        dp[i+1] = max(dp[i], dp[i+1]);
        for(int d=3;i+d<=N;d+=3){
            dp[i+d] = max(dp[i] + ok[i][i+d], dp[i+d]);
        }
    }
    cout << dp.back() << endl;
}