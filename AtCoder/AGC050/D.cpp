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

long long calcInv(long long a){
    return modPow(a, MOD-2);
}

int N;
vector<long long> mem[41][41][41][41];

vector<long long> solve(int R, int K, int id, int turn){
    if(!mem[R][K][id][turn].empty()){
        return mem[R][K][id][turn];
    }
    if(N-R == K){
        return mem[R][K][id][turn] = vector<long long>(R, 0);
    }
    // (K-turn) : candidate
    // (N-R) : opened
    // (N-R-t) : failure
    // fail
    vector<long long> res(R, 0);
    if(N-R-turn > 0){
        auto next = id+1 == R ? solve(R, K, 0, turn+1) : solve(R, K, id+1, turn);
        long long prob = (N-R-turn) * calcInv(K-turn) % MOD;
        for(int i=0;i<R;i++) res[i] = (res[i] + prob * next[i]) % MOD;
    }
    // get
    if(K > N-R){
        auto next = id == R-1 ? solve(R-1, K, 0, turn+1) : solve(R-1, K, id, turn);
        long long prob = (K-(N-R)) * calcInv(K-turn) % MOD;
        for(int i=0;i<id;i++) res[i] = (res[i] + prob * next[i]) % MOD;
        res[id] = (res[id] + prob) % MOD;
        for(int i=id;i<R-1;i++) res[i+1] = (res[i+1] + prob * next[i]) % MOD;
    }
    return mem[R][K][id][turn] = res;
}

int main(){
    int K; cin >> N >> K;
    auto res = solve(N, K, 0, 0);
    for(auto& t : res) cout << t << endl;

}