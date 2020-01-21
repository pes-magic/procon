#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 998244353;

int main(){
    long long N;
    string S;
    while(cin >> N >> S){
        vector<long long> dig(N+1, 0);
        for(int i=0;i<N;i++) dig[i+1] = (2*dig[i]+S[i]-'0')%MOD;
        vector<long long> key;
        vector<long long> num;
        long long res = 0;
        for(int div=(N-1)/2*2+1;div>=1;div-=2){
            if(N%div) continue;
            const long long d = N/div;
            long long cur = dig[d];
            bool ok = true;
            for(int i=0;i<N;i++){
                int cmp = S[i%d] - '0';
                if(i/d%2) cmp = 1 - cmp;
                if(S[i] - '0' < cmp) ok = false;
                else if(S[i] - '0' > cmp) break;
            }
            if(ok) cur = (cur+1) % MOD;
            for(int i=0;i<key.size();i++){
                if(d%key[i] == 0) cur = (cur + MOD - num[i]) % MOD;
            }
            key.push_back(d);
            num.push_back(cur);
            res = (res + 2 * d * cur) % MOD;
        }
        cout << res << endl;
    }
}