#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main(){
    int H; cin >> H;
    vector<int> P(1<<H);
    for(int i=P.size()/2;i<P.size();i++){
        cin >> P[i];
        P[i] += P.size()/2 - 1;
    }
    vector<long long> A(1<<H, 0);
    vector<long long> M(1<<H, 0);
    long long res = 0;
    for(int i=P.size()/2;i<P.size();i++) M[i] = i;
    for(int s=P.size()/2-1;s;s--){
        int l = s, r = s;
        while(2*l < P.size()){
            l = 2 * l;
            r = 2 * r + 1;
        }
        ++r;
        for(int i=l;i<(l+r)/2;i++){
            M[i] = (M[i] * s) % MOD;
            long long c = M[i];
            int p = P[i];
            while(p){
                c = c * p % MOD;
                A[p] = (A[p] + c) % MOD;
                p /= 2;
            }
        }
        for(int i=(l+r)/2;i<r;i++){
            long long c = M[i];
            M[i] = (M[i] * s) % MOD;
            int p = P[i];
            long long add = 0;
            while(p){
                add = (add * p) % MOD;
                res = (res + c * A[p] + MOD - add) % MOD;
                add = (c * A[p]) % MOD;
                add = (add * p) % MOD;
                c = c * p % MOD;
                p /= 2;
            }
        }
        for(int i=l;i<(l+r)/2;i++){
            int p = P[i];
            while(p){
                A[p] = 0;
                p /= 2;
            }
        }
    }
    cout << res << endl;
}
