#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

const long long INF = (1LL << 60);

int solve(const vector<long long>& a, long long K){
    if(accumulate(a.begin(), a.end(), 0LL) == K) return 1;
    const int N = a.size();
    vector<long long> dp(N+1, INF);
    dp[0] = 0;
    long long sum = 0;
    for(auto& t : a){
        vector<long long> next(N+1, INF);
        for(int i=0;i<dp.size();i++){
            if(dp[i] == INF) continue;
            next[i] = min(next[i], dp[i]);
            long long req = (sum == 0 ? 1 : dp[i]*(sum+t)/sum + 1 - dp[i]);
            if(req <= t){
                next[i+1] = min(next[i+1], dp[i]+req);
            }
        }
        sum += t;
        dp = next;
    }
    for(int i=N;i>=0;i--) if(dp[i] <= K) return i;
    return 0;
}

int main(){
    int N; long long K;
    while(cin >> N >> K){
        vector<long long> a(N);
        for(auto& t : a) cin >> t;
        cout << solve(a, K) << endl;
    }
}