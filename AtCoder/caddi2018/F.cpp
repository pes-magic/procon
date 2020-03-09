#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int MOD = 998244353;

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

int bitCount(int t){
    int res = 0;
    for(int i=t;i;i&=i-1) ++res;
    return res;
}

int main(){
    int N, M;
    while(cin >> N >> M){
        vector<map<int, int>> mp(N);
        for(int i=0;i<M;i++){
            int a, b, c;
            cin >> a >> b >> c;
            mp[a-1][b-1] = c;
        }
        vector<long long> dp(2, 0LL);
        if(mp[0].count(0)){
            dp[mp[0][0]] = 1;
        } else {
            dp[0] = dp[1] = 1;
        }
        for(int i=0;i<N-1;i++){
            vector<long long> next(2, 0LL);
            for(int j=0;j<16;j++){
                if(bitCount(j)%2) continue;
                bool ok = true;
                for(int k=0;k<4;k++){
                    int da = k%2, db = k/2;
                    int c = (j>>k)%2;
                    if(mp[i+da].count(i+db)){
                        if(mp[i+da][i+db] != c) ok = false;
                    }
                }
                if(!ok) continue;
                int m = 1;
                if(i > 0){
                    if(mp[i-1].count(i+1)){
                        if(mp[i+1].count(i-1)){
                            if((mp[i-1][i+1] + mp[i+1][i-1])%2 != j%2) continue; 
                        }
                    } else if(!mp[i+1].count(i-1)){
                        m = 2;
                    }
                }
                next[(j>>3)%2] += m * dp[j%2];
                next[(j>>3)%2] %= MOD;
            }
            dp = next;
        }
        long long res = (dp[0]+dp[1])%MOD;
        long long sub = 0;
        for(int i=0;i<N;i++){
            for(auto& p : mp[i]){
                if(abs(p.first - i) <= 2) continue;
                if(mp[p.first].count(i)){
                    if(mp[i][p.first] != mp[p.first][i]) res = 0;
                    if(i < p.first) ++sub;
                } else {
                    ++sub;
                }
            }
        }
        if(N >= 4){
            res *= modPow(2, (N-2LL)*(N-3LL)/2 - sub);
            res %= MOD;
        }
        cout << res << endl;
    }
}