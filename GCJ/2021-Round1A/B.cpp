#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

long long solveSmall(const vector<int>& P, const vector<long long>& N){
    long long sum = 0;
    for(int i=0;i<P.size();i++) sum += P[i] * N[i];
    vector<long long> dp(sum+1, -1);
    dp[1] = 0;
    for(int i=0;i<P.size();i++){
        for(int j=dp.size()-1;j>=1;j--){
            if(dp[j] == -1) continue;
            long long m = 1;
            auto base = dp[j];
            for(int k=0;k<=N[i];k++){
                if(m*j >= dp.size()) break;
                dp[m*j] = base + (N[i]-k) * P[i];
                m *= P[i];
            }
        }
    }
    long long res = 0;
    for(int k=1;k<dp.size();k++){
        if(dp[k] != -1) cout << k << " " << dp[k] << endl;
        if(dp[k] == k) res = k;
    }
    return res;
}

long long solve(const vector<int>& P, const vector<long long>& N){
    long long sum = 0;
    for(int i=0;i<P.size();i++) sum += P[i] * N[i];
    for(long long target=sum;target>=max(1LL, sum-30000);target--){
        vector<int> cnt(P.size(), 0);
        long long v = target;
        long long rest = sum;
        bool ok = true;
        for(int i=0;i<P.size();i++){
            while(v%P[i] == 0){
                v /= P[i];
                ++cnt[i];
                if(cnt[i] > N[i]) ok = false;
                rest -= P[i];
            }
            if(!ok) break;
        }
        if(!ok) continue;
        if(v != 1) continue;
        if(rest == target) return target;
    }
    return 0;
}

int main(){
    int T; cin >> T;
    for(int i=1;i<=T;i++){
        int M; cin >> M;
        vector<int> P(M);
        vector<long long> N(M);
        for(int i=0;i<M;i++) cin >> P[i] >> N[i];
        auto res = solve(P, N);
        printf("Case #%d: %lld\n", i, res);
    }
}
