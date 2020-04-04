#include <iostream>
#include <vector>
#include <set>

using namespace std;

void divs(set<long long>& S, long long t){
    if(t > 1) S.insert(t);
    for(long long d=2;d*d<=t;d++){
        if(t%d != 0) continue;
        S.insert(d);
        S.insert(t/d);
    }
}

long long test(long long N, long long K){
    while(N%K == 0) N /= K;
    return N%K;
}

int main(){
    long long N;
    while(cin >> N){
        set<long long> S;
        divs(S, N);
        divs(S, N-1);
        int res = 0;
        for(auto& t : S) if(test(N, t) == 1) ++res;
        cout << res << endl;
    }
}