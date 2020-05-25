#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 998244353;

int main(){
    int N; cin >> N;
    string X; cin >> X;
    vector<long long> div;
    for(int i=1;i<=N;i++) if(N%i == 0 && N/i%2 == 1) div.push_back(i);
    vector<long long> cnt(N+1, 0);
    long long res = 0;
    for(auto& d : div){
        string s[2] = {"", ""};
        long long num = 0;
        for(int i=0;i<d;i++){
            num = (2 * num + X[i] - '0') % MOD;
            s[0] += X[i];
            s[1] += X[i] == '0' ? '1' : '0';
        }
        bool ok = true;
        for(int i=0;i<N;i++){
            if(X[i] < s[i/d%2][i%d]) { ok = false; break; }
            if(X[i] > s[i/d%2][i%d]) break;
        }
        cnt[d] = (num + (ok ? 1 : 0)) % MOD;
        for(auto& d2 : div){
            if(d2 >= d) break;
            if(d%d2 == 0) cnt[d] = (cnt[d] + MOD - cnt[d2]) % MOD;
        }
        res = (res + cnt[d] * 2 * d) % MOD;
    }
    cout << res << endl;
    // for(int N=1;N<=20;N++){
    //     vector<int> cycle(1<<N, -1);
    //     for(int i=0;i<(1<<N);i++){
    //         if(cycle[i] != -1) continue;
    //         int t = i;
    //         int c = 0;
    //         do {
    //             c++;
    //             t = ((1-t%2)<<(N-1)) + t/2;
    //         } while(t != i);
    //         do {
    //             cycle[t] = c;
    //             t = ((1-t%2)<<(N-1)) + t/2;
    //         } while(t != i);
    //         if(c != 2*N){
    //             cout << N << " " << c << ":";
    //             for(int j=N-1;j>=0;j--) cout << (i>>j)%2;
    //             cout << endl;
    //         }
    //     }
    // }
}