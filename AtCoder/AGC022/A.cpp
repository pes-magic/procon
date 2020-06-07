#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    string S; cin >> S;
    if(S.size() == 26){
        auto T = S;
        if(!next_permutation(T.begin(), T.end())){
            cout << -1 << endl;
        } else {
            for(int i=0;i<26;i++){
                cout << (char)T[i];
                if(T[i] != S[i]) break;
            }
            cout << endl;
        }
    } else {
        cout << S;
        for(int i=0;i<26;i++){
            if(S.find('a'+i) == string::npos){
                cout << (char)('a'+i) << endl;
                break;
            }
        }
    }
}