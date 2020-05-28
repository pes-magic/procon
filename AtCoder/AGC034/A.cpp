#include <iostream>
#include <string>

using namespace std;

int main(){
    int N, A, B, C, D;
    cin >> N >> A >> B >> C >> D;
    --A; --B; --C; --D;
    string S; cin >> S;
    bool valid = true;
    bool jump = false;
    for(int i=A;i<C;i++){
        if(S[i] == '#' && S[i+1] == '#') valid = false;
    }
    for(int i=B;i<=D;i++){
        if(i+1 < N && S[i] == '#' && S[i+1] == '#') valid = false;
        if(i+1 < N && S[i-1] == '.' && S[i] == '.' && S[i+1] == '.') jump = true;
    }
    if(C > D && !jump) valid = false;
    cout << (valid ? "Yes" : "No") << endl;
}