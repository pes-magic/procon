#include <iostream>
#include <string>

using namespace std;

bool ok(const string& S, int L){
    for(int i=0;i<L-i-1;i++) if(S[i] != S[L-i-1]) return false;
    return true;
}

int main(){
    string S;
    while(cin >> S){
        int N = S.size();
        cout << (ok(S, N) && ok(S, N/2) ? "Yes" : "No") << endl;
    }
}