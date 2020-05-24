#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

long long pow10(long long p){
    long long res = 1;
    long long cur = 10;
    while(p){
        if(p%2) res = (res*cur)%MOD;
        cur = (cur*cur)%MOD;
        p /= 2;
    }
    return res;
}

vector<long long> makeGrundy(int N){
    int M; cin >> M;
    vector<vector<int>> g(N+1);
    for(int i=0;i<M;i++){
        int a, b; cin >> a >> b;
        if(a > b) swap(a, b);
        g[a].push_back(b);
    }
    vector<int> grundy(N+1);
    vector<long long> res(512, 0);
    grundy[N] = 0;
    res[0] = pow10(18*N);
    for(int i=N-1;i>=1;i--){
        vector<int> visit(512, 0);
        for(auto& t : g[i]){
             visit[grundy[t]] = 1;
        }
        for(int j=0;j<512;j++){
            if(!visit[j]){
                grundy[i] = j;
                res[j] = (res[j] + pow10(18*i)) % MOD;
                break;
            }
        }
    }
    return res;
}

int main(){
    int N; cin >> N;
    auto g1 = makeGrundy(N);
    auto g2 = makeGrundy(N);
    auto g3 = makeGrundy(N);
    long long res = 0;
    for(int i=0;i<512;i++){
        for(int j=0;j<512;j++){
            res = (res + g1[i] * g2[j] % MOD * g3[i^j] % MOD) % MOD;
        }
    }
    cout << res << endl;
}