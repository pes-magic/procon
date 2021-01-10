#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int bitCount(int t){
    int res = 0;
    for(int i=t;i;i&=i-1) ++res;
    return res;
}

void zetaTransform(vector<long long>& v, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<v.size();j++){
            if(j&(1<<i)) v[j] = (v[j] + v[j^(1<<i)]) % MOD;
        }
    }
}

void mobiusTransform(vector<long long>& v, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<v.size();j++){
            if(j&(1<<i)) v[j] = (v[j] + MOD - v[j^(1<<i)]) % MOD;
        }
    }
}

vector<long long> subsetConvolution(const vector<long long>& a, const vector<long long>& b, int n){
    auto zeta = [&](const vector<long long>& v){
        vector<vector<long long>> res(n+1, vector<long long>(1<<n, 0));
        for(int i=0;i<(1<<n);i++) res[bitCount(i)][i] = v[i];
        for(auto& r : res) zetaTransform(r, n);
        return res;
    };
    auto az = zeta(a);
    auto bz = zeta(b);
    vector<vector<long long>> cz(n+1, vector<long long>(1<<n, 0));
    for(int i=0;i<(1<<n);i++){
        for(int j=0;j<=n;j++){
            for(int k=0;k<=j;k++) cz[j][i] = (cz[j][i] + az[k][i] * bz[j-k][i]) % MOD;
        }
    }
    for(auto& v : cz) mobiusTransform(v, n);
    vector<long long> res(1<<n, 0);
    for(int i=0;i<res.size();i++) res[i] = cz[bitCount(i)][i];
    return res;
}

int main(){
    int N; cin >> N;
    vector<long long> f(1<<N), g(1<<N);
    for(auto& t : f) cin >> t;
    for(auto& t : g) cin >> t;
    auto v = subsetConvolution(f, g, N);
    cout << v[0];
    for(int i=1;i<v.size();i++) cout << " " << v[i];
    cout << endl;
}