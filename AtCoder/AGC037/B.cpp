#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 998244353;

int main(){
    int N;
    while(cin >> N){
        string S; cin >> S;
        vector<int> cnt(256, 0);
        long long res = 1;
        for(int i=1;i<=N;i++) res = (res * i) % MOD;
        for(auto c : S){
            int cur = cnt[c];
            int next = 3*N;
            for(auto t : "RGB"){
                if(t == c) continue;
                if(cnt[t] > cur) next = min(next, cnt[t]);
            }
            if(next != 3*N){
                res = (res * (next - cur)) % MOD;
            }
            ++cnt[c];
        }
        cout << res << endl;
    }
}