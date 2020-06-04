#include <iostream>
#include <vector>
#include <string>

using namespace std;

long long valid(const string& S, const string& r, const string& b){
    vector<vector<long long>> dp(r.size()+1, vector<long long>(b.size()+1, 0LL));
    dp[0][0] = 1;
    for(int i=0;i<=r.size();i++){
        for(int j=0;j<=b.size();j++){
            if(i < r.size() && r[i] == S[i+j]) dp[i+1][j] += dp[i][j];
            if(j < b.size() && b[j] == S[i+j]) dp[i][j+1] += dp[i][j];
        }
    }
    return dp[r.size()][b.size()];
}

int main(){
    int N; cin >> N;
    string S; cin >> S;
    string T;
    for(int i=2*N-1;i>=N;i--) T += S[i];
    long long res = 0;
    for(int i=0;i<(1<<N);i++){
        string r, b;
        for(int j=0;j<N;j++){
            if(i&(1<<j)) r += S[j];
            else b += S[j];
        }
        res += valid(T, r, b);
    }
    cout << res << endl;
}