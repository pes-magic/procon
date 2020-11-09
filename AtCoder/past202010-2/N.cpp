#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    vector<string> vs(18);
    for(auto& s : vs) cin >> s;
    vs.push_back("000000");
    vector<long long> dp(64*64, 0);
    dp[0] = 1;
    for(const auto& s : vs){
        for(int i=0;i<6;i++){
            vector<long long> next(64*64, 0);
            for(int k=0;k<(1<<12);k++){
                for(int j=0;j<2;j++){
                    if(s[i] != '?' && s[i]-'0' != j) continue;
                    int a = (k>>11)%2;
                    int b = (i==0 ? 0 : (k>>6)%2);
                    int c = (k>>5)%2;
                    int d = (i==5 ? 0 : (k>>4)%2);
                    int e = j;
                    int cnt = 0;
                    if(a == c) ++cnt;
                    if(b == c) ++cnt;
                    if(d == c) ++cnt;
                    if(e == c) ++cnt;
                    if(cnt < 2) continue;
                    next[(2*k+j)%(1<<12)] += dp[k];
                }
            }
            dp = next;
        }
    }
    long long res = 0;
    for(auto& t : dp) res += t;
    cout << res << endl;
}
