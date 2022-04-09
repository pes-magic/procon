#include <iostream>
#include <string>

using namespace std;

int main(){
    int T; cin >> T;
    for(int t=1;t<=T;t++){
        string S; cin >> S;
        string res = "";
        for(int i=S.size()-1;i>=0;i--){
            res = S[i] + res;
            if(S[i] + res < res) res = S[i] + res;
        }
        cout << "Case #" << t << ": " << res << endl;
    }
}