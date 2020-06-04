#include <iostream>
#include <vector>

using namespace std;

const int MOD = 1000000007;
const int inv2 = MOD - MOD/2;

long long modPow(long long a, long long p){
    if(p == 0) return 1;
    auto res = modPow(a, p/2);
    res = (res * res) % MOD;
    if(p%2 == 1) res = (res * a) % MOD;
    return res;
}

pair<long long, long long> solve(const vector<int>& h, int begin, int end, int curH){
    int lowest = 1 << 30, highest = curH;
    for(int i=begin;i<end;i++){
        lowest = min(lowest, h[i]);
        highest = max(highest, h[i]);
    }
    if(lowest == highest){
        return make_pair(modPow(2, lowest - curH), (modPow(2, end - begin) + MOD - 2) % MOD);
    }
    long long all = 1;
    long long one = 1;
    int last = -1;
    int cnt = 0;
    for(int i=begin;i<=end;i++){
        if(i == end || h[i] == lowest){
            if(i < end) ++cnt;
            if(last != -1){
                auto p = solve(h, last, i, lowest);
                all = (all * (2 * p.first + p.second)) % MOD;
                one = (one * p.first) % MOD;
                last = -1;
            }
        } else {
            if(last == -1) last = i;
        }
    }
    one = (2 * one) % MOD;
    all = (all * modPow(2, cnt)) % MOD;
    all = (all + MOD - one) % MOD;
    one = (one * modPow(2, lowest - curH - 1)) % MOD;
    return make_pair(one, all);
}

int main(){
    int N; cin >> N;
    vector<int> h(N);
    for(auto& t : h) cin >> t;
    auto res = solve(h, 0, N, 0);
    cout << (res.first + res.second) % MOD << endl;
}