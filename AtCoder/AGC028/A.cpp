#include <iostream>
#include <string>

using namespace std;

long long gcd(long long a, long long b){ return a%b ? gcd(b, a%b) : b; }
long long lcm(long long a, long long b){ return a/gcd(a, b)*b; }

int main(){
    long long N, M; cin >> N >> M;
    string S, T; cin >> S >> T;
    long long res = lcm(N, M);
    bool ok = true;
    int s = res/M;
    int t = res/N;
    for(int i=0;i*s<N;i++){
        if(S[i*s] != T[i*t]) ok = false;
    }
    cout << (ok ? res : -1) << endl;
}