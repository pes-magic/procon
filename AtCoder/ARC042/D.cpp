#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

long long modPow(long long a, long long p, int M){
    if(p == 0) return 1;
    auto res = modPow(a, p/2, M);
    res = (res * res) % M;
    if(p%2) res = (res * a) % M;
    return res;
}

int solveNaive(int X, int P, int A, int B){
    long long s = modPow(X, A, P);
    long long res = s;
    for(int i=A;i<B;i++){
        s = (s * X) % P;
        res = min(res, s);
    }
    return res;
}

int solve(int X, int P, int A, int B){
    if(B - A < (1LL << 24)) return solveNaive(X, P, A, B);
    A %= P - 1;
    B %= P - 1;
    int sq = sqrt(P);
    long long m = modPow(X, A, P);
    // 離散対数
    map<int, int> mp;
    for(int i=0;i<sq;i++){
        if(!mp.count(m)) mp[m] = i;
        m = (m * X) % P;
    }
    auto inv = modPow(modPow(X, sq, P), P-2, P);
    for(int i=1;;i++){
        int target = i;
        int find = -1;
        for(int j=0;j<=sq;j++){
            if(j * sq > B - A) break;
            if(mp.count(target)){
                find = j * sq + mp[target];
                break;
            }
            target = (target * inv) % P;
        }
        if(find != -1 && find <= B - A) return i;
    }
}

int main(){
    vector<pair<int, int>> m;
    int X, P, A, B;
    while(cin >> X >> P >> A >> B){
        int a = A/(P-1);
        int b = B/(P-1);
        cout << (a != b ? 1 : solve(X, P, A, B)) << endl;
        // if(a == b && B-A >= 10000000) m.emplace_back(B-A, solve(X, P, A, B));
    }
    // sort(m.begin(), m.end());
    // for(auto& p : m){
    //     cout << "if(dif == " << p.first << ") return " << p.second << ";" << endl;
    // }
}