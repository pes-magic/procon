#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

int main(){
    int N; cin >> N;
    string S; cin >> S;
    vector<vector<int>> cnt;
    vector<int> c(3, 0);
    cnt.push_back(c);
    for(int i=0;i<S.size();i++){
        if(S[i] == 'R') c[0]++;
        if(S[i] == 'G') c[1]++;
        if(S[i] == 'B') c[2]++;
        cnt.push_back(c);
    }
    for(auto& v : cnt) sort(v.begin(), v.end());
    long long res = 1;
    for(int i=2;i<=N;i++) res = (res * i) % MOD;
    for(int i=1;i<cnt.size();i++){
        for(int j=0;j<2;j++){
            if(cnt[i][j] > cnt[i-1][j]) res = (res * (cnt[i][j+1] - cnt[i-1][j])) % MOD;
        }
    }
    cout << res << endl;
}