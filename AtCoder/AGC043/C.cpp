#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res*res)%MOD;
    if(p%2) res = (res*a)%MOD;
    return res;
}

vector<int> grundy(int N){
    int M; cin >> M;
    vector<vector<int>> g(N);
    for(int i=0;i<M;i++){
        int a, b; cin >> a >> b;
        --a; --b;
        if(a > b) swap(a, b);
        g[a].push_back(b);
    }
    vector<int> res(N);
    vector<int> gr(N, 0);
    for(int i=N-1;i>=0;i--){
        for(int j=0;j<=g[i].size();j++) gr[j] = 0;
        for(auto& t : g[i]) gr[res[t]] = 1;
        for(int j=0;;j++){
            if(!gr[j]){ res[i] = j; break; }
        }
    }
    return res;
}

int main(){
    int N;
    while(cin >> N){
        vector<long long> res(1024, 0);
        res[0] = 1;
        for(int i=0;i<3;i++){
            auto gr = grundy(N);
            vector<long long> dst(1024, 0);
            vector<long long> next(1024, 0);
            for(int j=0;j<N;j++){
                dst[gr[j]] += modPow(10, 18*(j+1));
                dst[gr[j]] %= MOD;
            }
            for(int j=0;j<1024;j++){
                for(int k=0;k<1024;k++){
                    next[k^j] += res[k] * dst[j];
                    next[k^j] %= MOD;
                }
            }
            res = next;
        }
        cout << res[0] << endl;
    }
}