#include <iostream>
#include <string>

using namespace std;

long long solve(const string& S, int k){
    int dst = 0;
    long long res = 0;
    long long cnt = 0;
    int m = 0;
    int c = 0;
    for(int i=0;i<S.size();i++){
        while(dst < S.size() && dst - i < k){
            if(S[dst] == 'M') ++m;
            if(S[dst] == 'C'){ ++c; cnt += m; }
            ++dst;
        }
        if(S[i] == 'D') res += cnt;
        if(S[i] == 'M') { cnt -= c; --m; }
        if(S[i] == 'C') --c;
    }
    return res;
}

int main(){
    int N; cin >> N;
    string S; cin >> S;
    int Q; cin >> Q;
    for(int i=0;i<Q;i++){
        int k; cin >> k;
        cout << solve(S, k) << endl;
    }
}