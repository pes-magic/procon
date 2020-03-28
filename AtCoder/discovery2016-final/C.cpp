#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int MOD = 1000000007;

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

long long calcInv(long long a){
    return modPow(a, MOD-2);
}

vector<long long> solve(const string& S, int& pos, int K){
    const long long inv2 = calcInv(2);
    vector<long long> res(1, 1);
    while(pos < S.size() && S[pos] == '('){
        ++pos;
        auto inner = solve(S, pos, K);
        vector<long long> in(min<int>(K+1, inner.size()+1), 0);
        for(int i=0;i<inner.size();i++){
            for(int j=-1;j<=1;j++){
                if(abs(i+j) >= in.size()) continue;
                in[abs(i+j)] = (in[abs(i+j)] + (j==0 ? 2 : 1) * inner[i]) % MOD;
            }
        }
        vector<long long> next(res.size() + in.size() - 1, 0);
        for(int i=0;i<res.size();i++){
            for(int j=0;j<in.size();j++){
                if(i == 0) next[j] = (next[j] + res[i]*in[j]) % MOD;
                else if(j==0) next[i] = (next[i] + res[i]*in[j]) % MOD;
                else {
                    auto add = (res[i]*in[j]) % MOD * inv2 % MOD;
                    if(i+j < next.size()) next[i+j] = (next[i+j] + add) % MOD;
                    next[abs(i-j)] = (next[abs(i-j)] + add) % MOD;
                }
            }
        }
        res = next;
        ++pos;
    }
    return res;
}

int main(){
    string S;
    while(cin >> S){
        int K; cin >> K;
        K /= 2;
        int pos = 0;
        auto res = solve(S, pos, K);
        long long sum = 0;
        for(auto& t : res) sum = (sum + t) % MOD;
        cout << sum << endl;
    }
}