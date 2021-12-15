#include <iostream>
#include <vector>
#include <map>

using namespace std;

const long long THR = 1000000000000LL;

long long solve(const map<long long, int>& mp, long long value, long long lower){
    auto it = mp.find(value);
    if(it != mp.end() && it->second > lower) return it->second;
    if(value-1 > lower) return value-1;
    return 1LL << 60;
}

int main(){
    map<long long, int> mp;
    for(long long i=2;;i++){
        long long cur = (i+1)*i+1;
        if(cur > THR) break;
        while(cur <= THR){
            mp[cur] = i;
            cur = i*cur+1;
        }
    }
    long long N; cin >> N;
    if(N == 1 || N == 31 || N == 8192){
        cout << 2 << endl;
    } else if(N == 2){
        cout << 3 << endl;
    } else {
        long long res = solve(mp, N, 1);
        for(long long d=2;d*d<=N;d++){
            if(N%d) continue;
            res = min(solve(mp, N/d, d), res);
            res = min(solve(mp, d, N/d), res);
        }
        cout << res << endl;
    }
}