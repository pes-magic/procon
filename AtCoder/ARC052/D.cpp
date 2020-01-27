#include <iostream>
#include <vector>

using namespace std;

int dmod(long long v, long long m){
    long long res = 0;
    while(v){
        res = (res + v%10) % m;
        v /= 10;
    }
    return res;
}

long long solve(long long K, long long M){
    vector<vector<long long>> dp(2, vector<long long>(K, 0));
    dp[1][0] = 1;
    vector<long long> digit;
    vector<long long> m10(1, 1);
    for(auto k=M;k;k/=10) digit.push_back(k%10);
    while(m10.size() < digit.size()) m10.push_back(m10.back()*10%K);
    for(int i=m10.size()-1;i>=0;i--){
        vector<vector<long long>> next(2, vector<long long>(K, 0));
        for(int j=0;j<K;j++){
            for(int k=0;k<10;k++){
                long long nextKey = (j + k * m10[i] + 10 * K - k) % K;
                next[0][nextKey] += dp[0][j];
                if(k <= digit[i]){
                    next[k < digit[i] ? 0 : 1][nextKey] += dp[1][j];
                }
            }
        }
        dp = next;
    }
    return dp[0][0] + dp[1][0] - 1; // remove 0
}

long long naive(long long K, long long M){
    long long res = 0;
    for(int i=0;;i++){
        for(int j=0;j<min(K, 100LL);j++){
            if(i*K+j > M) return res-1;
            if(dmod(i*K+j, K) == j) ++res;
        }
    }
    return -1;
}

int main(){
    long long K, M;
    while(cin >> K >> M){
        cout << (K < 100000 ? solve(K, M) : naive(K, M)) << endl;
    }
}