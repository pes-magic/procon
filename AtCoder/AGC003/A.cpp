#include <iostream>
#include <string>

using namespace std;

bool check(string& S){
    string c = "NWSE";
    for(int i=0;i<4;i++){
        if(S.find(c[i]) != string::npos && S.find(c[(i+2)%4]) == string::npos) return false;
    }
    return true;
}

int main(){
    string S;
    while(cin >> S){
        cout << (check(S) ? "Yes" : "No") << endl;
    }
}