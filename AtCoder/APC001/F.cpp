#include <iostream>
#include <vector>

using namespace std;

int valid(int mask){
    int res = 0;
    for(int i=0;i<15;i++) if(mask&(1<<i)) res ^= i+1;
    return res == 0;
}

int main(){
    int N; cin >> N;
    vector<int> v(N, 0);
    for(int i=0;i<N-1;i++){
        int a, b, c; cin >> a >> b >> c;
        v[a] ^= c;
        v[b] ^= c;
    }
    int res = 0;
    vector<int> cnt(15, 0);
    for(auto& t : v){
        if(t == 0) continue;
        cnt[t-1]++;
    }
    for(auto& t : cnt){
        res += t/2;
        t %= 2;
    }
    vector<int> dp(1<<15, 0);
    for(int i=1;i<(1<<15);i++){
        if(!valid(i)) continue;
        for(int j=i;j;j=i&(j-1)){
            if(j != i && valid(j)){
                dp[i] = max(dp[i], dp[j] + dp[i^j] + 1);
            }
        }
    }
    int c = 0;
    int m = 0;
    for(int i=0;i<15;i++){
        if(!cnt[i]) continue;
        m |= (1<<i);
        c++;
    }
    if(m) res += c - 1 - dp[m];
    cout << res << endl;
}