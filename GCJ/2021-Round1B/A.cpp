#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

const long long G = 1000000000;
const long long day = 12 * 60 * 60 * G;

vector<long long> solve(vector<long long> T){
    auto toTick = [&](const long long from, const long long to){
        return (to - from + day) % day;
    };
    for(long long sec=0;sec<12*60*60;sec++){
        long long H = sec * G;
        long long M = H * 12 % day;
        long long S = M * 60 % day;
        do {
            long long mov = toTick(T[0], H);
            long long h = (T[0]+mov)%day;
            long long m = (T[1]+mov)%day;
            long long s = (T[2]+mov)%day;
            long long movM = toTick(M, m);
            long long dM = movM/11;
            long long movS = toTick(S, s);
            long long dS = movS/719;
            if(movM%11 != 0) continue;
            if(dM >= G) continue;
            if(movS%719 != 0) continue;
            if(dM != dS) continue;
            return vector<long long>{sec/60/60, sec/60%60, sec%60, dM};
        } while(next_permutation(T.begin(), T.end()));
    }
    return vector<long long>{0, 0, 0, 0};
}

int main(){
    int T; cin >> T;
    for(int i=1;i<=T;i++){
        vector<long long> V(3);
        cin >> V[0] >> V[1] >> V[2];
        auto res = solve(V);
        printf("Case #%d: %lld %lld %lld %lld\n", i, res[0], res[1], res[2], res[3]);
    }
}
