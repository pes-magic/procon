#include <iostream>

using namespace std;

long long solve(long long t){
    if(t <= 0) return 0;
    long long s = (t/4)*4;
    long long res = 0;
    for(auto i=s;i<=t;i++) res ^= i;
    return res;
}

int main(){
    long long A, B;
    while(cin >> A >> B){
        cout << (solve(B)^solve(A-1)) << endl;
    }
}